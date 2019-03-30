#if ! defined(CCOM_CCOMOBJECTBASE_HPP)
#define CCOM_CCOMOBJECTBASE_HPP 1

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  Disclaimer: This file is an adaptation of the original code proposal of
//    Bogdan Dragu.
//
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <CCom/Types.hpp>

#include <iostream>

namespace CCom
{
#if __cpp_variadic_templates

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  CComObjectBase_QI - class that provides impl_QueryInterface and derives
  //    from all the interfaces.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class... Interfaces>
  struct CComObjectBase_QI;

  template <class Head, class... Tail>
  struct CComObjectBase_QI <Head, Tail...>
  : Head
  , CComObjectBase_QI <Tail...>
  {
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  impl_QueryInterface
    //
    //  Checks the IID against all interfaces and returns a pointer to the
    //    matched interface if it finds the IID
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void *
    impl_QueryInterface
    (RefIID iid)
    noexcept
    {
      if (iid == IID_Traits <Head>::iid)
        return static_cast <Head *> (this);
      else
        return CComObjectBase_QI <Tail...>::impl_QueryInterface (iid);
    }
  };

  template <>
  struct CComObjectBase_QI <>
  {
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  impl_QueryInterface
    //
    //  Stop condition for the template recursion. If no IID has been matched
    //    return nullptr.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void *
    impl_QueryInterface
    (RefIID iid)
    noexcept
    {
      static_cast <void> (iid);
      return nullptr;
    }
  };

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  CComObjectBase - helper class which takes away the implementation of the
  //    IUnknown specific methods from the end-user. It implements all the
  //    mandatory methods: queryInterface, addRef and release.
  //
  //  This class derives from CComObjectBase_QI which in turn derives from all
  //    the interfaces.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class Final, class... Interfaces>
  struct CComObjectBase;

  template <class Final, class Head, class ...Tail>
  struct CComObjectBase <Final, Head, Tail...>
  : CComObjectBase_QI <Head, Tail...>
  {
  public:
    RESULT
    queryInterface
    (RefIID iid, void **ppvInterface)
    noexcept override
    {
      if (! ppvInterface)
        return E_FAIL; // [2019-03-30] Should be E_POINTER.

      if (isIUnknown (iid))
      {
        *ppvInterface =
          static_cast <IUnknown *> (static_cast <Head *> (this));
        addRef ();

        return S_OK;
      }
      else if (void *const pvResult = this->impl_QueryInterface (iid))
      {
        *ppvInterface = pvResult;
        addRef ();

        return S_OK;
      }
      else
      {
        *ppvInterface = nullptr;
        return E_NOINTERFACE;
      }
    }

  // [2019-03-27] BDragu: Should we provide some kind of access to the ref. cnt?
  private:
    uint32_t m_nRefCount;

  public:
    CComObjectBase
    ()
    noexcept
    : m_nRefCount {1}
    {}

    uint32_t
    addRef
    ()
    noexcept override
    {
      const uint32_t y = ++m_nRefCount;
      return y;
    }

    uint32_t
    release
    ()
    noexcept override
    {
      const uint32_t y = --m_nRefCount;

      if (y == 0)
      {
        // BDragu:
        // CRTP is used here. Needed because the destructor is not virtual.
        Final *const pToDelete = static_cast <Final *> (this); // Downcast.
        delete pToDelete;
      }

      return y;
    }
  };

#else
  #error "CComObjectBase requires support for variadic templates"
#endif

}

#endif // CCOM_CCOMOBJECTBASE_HPP

