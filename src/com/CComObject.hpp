#if !defined(EXPERIMENTAL_CCOMOBJECT_HPP)
#define EXPERIMENTAL_CCOMOBJECT_HPP 1

#include <interface/IUnknown.hpp>

#include <iostream>
#include <memory>

namespace HIT
{
  template <typename IDesired = IUnknown>
  class CComObject
  {
  public:
    CComObject()
    : m_pObject{nullptr}
    {}

    template <typename IOther>
    CComObject(const CComObject<IOther>& other)
    : m_pObject{nullptr}
    {
      std::cout << "CComObject(const CComObject<IOther>&)\n";
      other.queryInterface(IIDTraits<IDesired>::IID(),
        static_cast<void **> (
          static_cast<void *> (&m_pObject)));
    }

    template <typename IOther>
    CComObject& operator=(const CComObject<IOther>& other)
    {
      std::cout << "operator=\n";
      swap(std::move(CComObject(other)));
      return *this;
    }

    template <typename IOther>
    CComObject(CComObject<IOther>&& other)
    : m_pObject{nullptr}
    {
      swap(other);
    }

    template <typename IOther>
    CComObject& operator=(CComObject<IOther>&& other)
    {
      swap(other);
    }

    CComObject(IUnknown * pObject)
    : m_pObject{pObject}
    {
      if (! pObject)
        return;
      
      // pObject->addRef();
    }

    ~CComObject()
    {
      std::cout << "~CComObject() with ptr = " << m_pObject << "\n";
      if (m_pObject)
        m_pObject->release();
    }

    void swap(CComObject&& other) noexcept
    {
      std::swap(m_pObject, other.m_pObject);
    }

    operator bool() const
    {
      return (m_pObject != nullptr);
    }

  public:
    int queryInterface(const RefIID iid, void **ppvInterface) const
    {
      return m_pObject->queryInterface(iid, ppvInterface);
    }

  public:
    IDesired* operator->() const
    {
      return static_cast<IDesired *> (m_pObject);
    }

  private:
    IUnknown * m_pObject;
  };
}

#endif // EXPERIMENTAL_CCOMOBJECT_HPP

