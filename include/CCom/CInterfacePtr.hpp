// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  Copyright 2019 Alexandru N. Onea (alexandru.onea@toporcomputing.com)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#if ! defined(CCOM_CINTERFACEPTR_HPP)
#define CCOM_CINTERFACEPTR_HPP 1

#include <CCom/Types.hpp>

#include <algorithm> // needed for swap

namespace CCom
{
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  NoAddRefReleaseOnInterface - helper class which hides the addRef and
  //    release () methods from the interface, so that user don't accidentally
  //    call those methods while the object is managed by CInterfacePtr.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class IObject>
  class NoAddRefReleaseOnInterface
    : public IObject
  {
  protected:
    ~NoAddRefReleaseOnInterface
    ()
    {};

  private:
    // virtual uint32_t addRef  () = 0;
    // virtual uint32_t release () = 0;

    enum { addRef, release };
  };

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  CInterfacePtr - smart pointer implementation for COM-like object. It
  //    provides means to access interfaces and navigate hierarchies, while
  //    managing the object lifetime. This is an intrusive smart pointer since
  //    it relies on the object to have implemented addRef and release for
  //    incrementing and decrementing a reference count.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class IDesired = IUnknown>
  class CInterfacePtr
  {
  private:
    IUnknown * m_pSelf;

  public:
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Swap operation
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void
    swap
    (CInterfacePtr &other)
    noexcept
    {
      std::swap (m_pSelf, other.m_pSelf);
    }

  public:
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Destructor
    //
    //  As long as the interface pointer inside is valid, we call release () 
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ~CInterfacePtr
    ()
    {
      if (m_pSelf)
        m_pSelf->release ();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Empty constructor
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr
    ()
    : m_pSelf {nullptr}
    {}

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Constructor from raw interface pointer.
    //
    //  When constructing a CInterfacePtr from a raw pointer, we also call
    //  addRef () on the raw interface because. This is the default behaviour
    //  and it is enforced because we cannot assume anything about the origins
    //  on the raw pointers (i.e. it might still be used as far as we are
    //  concerned).
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    explicit
    CInterfacePtr
    (IDesired * pSelf)
    : m_pSelf {pSelf}
    {
      if (m_pSelf)
        m_pSelf->addRef ();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Copy assignment operator from raw interface pointer.
    //
    //  When constructing a CInterfacePtr from a raw pointer, we also call
    //  addRef () on the raw interface because. This is the default behaviour
    //  and it is enforced because we cannot assume anything about the origins
    //  on the raw pointers (i.e. it might still be used as far as we are
    //  concerned).
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr &
    operator=
    (IDesired * pSelf)
    {
      CInterfacePtr tmp {pSelf};
      swap (tmp);
      return *this;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Copy constructor
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr
    (const CInterfacePtr &other)
    : CInterfacePtr (other.m_pSelf)
    {}

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Copy assignment operator
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr &
    operator=
    (const CInterfacePtr &other)
    {
      swap (CInterfacePtr (other));
      return *this;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Conversion operations are disabled by default. See Cast.hpp for more
    //    details. You can still enable them by providing the definition below.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#if defined (CCom_INTERFACEPTR_ENABLE_CONVERSION_CTOR)
  public:
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Conversion constructor from another CInterfacePtr
    //
    //  The purpose of the conversion constructor is to implicitely call the
    //  queryInterface () method of the object and try to obtain a pointer to
    //  the desired interface. If the operation succeeds, the constructed
    //  CInterfacePtr will hold a pointer that can be used to access the desired
    //  interface. Otherwise, it will create an empty CInterfacePtr.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <class IOther>
    CInterfacePtr
    (const CInterfacePtr <IOther> &other)
    : m_pSelf {nullptr}
    {
      CInterfacePtr<IDesired> tmp;
      other.queryInterface (tmp);
      swap (tmp);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Conversion assignment operator
    //
    //  This operator is implemented in terms of the conversion constructor.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <class IOther>
    CInterfacePtr &
    operator=
    (const CInterfacePtr <IOther> &other)
    {
      swap (CInterfacePtr (other));
      return *this;
    }
#endif

  public:
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Move constructor
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr
    (CInterfacePtr&& other)
    noexcept
    // For built-ins (e.g. raw pointers), move operations copy without
    // modifying the source. The following std::move is only for clarity.
    // But we have to nullify the source ourselves.
    : m_pSelf {std::move (other.m_pSelf)}
    {
      other.m_pSelf = nullptr;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Move operator
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    CInterfacePtr &
    operator=
    (CInterfacePtr&& other)
    noexcept
    {
      swap (std::move (other));
      return *this;
    }

  public:
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  queryInterface
    //
    //  This operation abstracts the GUIDs of the interfaces by templating.
    //  The result is always either a valid CInterfacePtr which can be used to
    //  access the desired interface, or an empty CInterfacePtr.
    //
    //  [22.03.2019] Should we allow the option to throw exceptions here?
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    template <class IOther>
    RESULT
    queryInterface
    (CInterfacePtr <IOther> &other)
    const
    {
      IOther *pOther;
      const auto res = m_pSelf->queryInterface
      (
        IID_Traits <IOther>::iid,
        toVoidPtrPtr (&pOther)
      );

      if (FAILED (res))
        return res;

      other.attach (pOther);
      return res;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  attach
    //
    //  Attach a raw interface pointer to this CInterfacePtr without calling
    //  addRef (). This is useful when creating the CInterfacePtr for the first
    //  time by, for eg. calling queryInterface on IUnknown or directly from
    //  the DL entry point.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void
    attach
    (IDesired * p)
    noexcept
    {
      if (m_pSelf)
        m_pSelf->release ();

      m_pSelf = p;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  detach
    //
    //  Removes the pointer from this CInterfacePtr without calling release ()
    //  This is known as the "release" operation of smart pointers such as
    //  shared_ptr and unique_ptr. The different choice of naming here is
    //  intentional, to make sure that users will have a common understanding
    //  of what release does (i.e. decrementing the reference count of the
    //  interface pointer).
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    IDesired *
    detach
    ()
    noexcept
    {
      IDesired * const pRet = m_pSelf;
      m_pSelf = nullptr;
      return pRet;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  get
    //
    //  Returns the interface pointer to the desired interface.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    IDesired *
    get
    ()
    const noexcept
    {
      return static_cast <IDesired *> (m_pSelf);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  Access operator
    //
    //  Allows access to the interface methods in a similar manner to other
    //  implementations of smart pointers. Using this without first checking
    //  whether the CInterfacePtr holds a valid object leads to horrible things.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    NoAddRefReleaseOnInterface <IDesired> *
    operator->
    ()
    const // noexcept ?
    {
      return static_cast <NoAddRefReleaseOnInterface <IDesired> *> (m_pSelf);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  bool operator
    //
    //  Returns true if the interface pointer within is valid and can be used
    //  to access the desired interface.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    explicit
    operator bool ()
    const noexcept
    {
      return (m_pSelf != nullptr);
    }
  };

} // namespace CCom

#include <CCom/Cast.hpp>

#endif // CCOM_CINTERFACEPTR_HPP

