#if ! defined(CCOM_DEMO_IMPL_CPAPER_HPP)
#define CCOM_DEMO_IMPL_CPAPER_HPP 1

#define CCOM_INSTANTIATE_IID 1

#include <iostream>

#include <CCom/Types.hpp>
#include <interface/IDrawable.hpp>

namespace CCom
{
  class CPaper : public IDrawable
  {
  public:
    CPaper()
    : m_nRefCount {1}
    {
      std::cout << "CPaper::CPaper()" << std::endl;
    }

    ~CPaper()
    {
      std::cout << "CPaper::~CPaper()" << std::endl;
    }

  public:
    virtual void draw() noexcept override;

  public:
    virtual RESULT queryInterface(const RefIID iid, void **ppvInterface) noexcept override
    {
      if (CCom::isIUnknown(iid))
      {
        *ppvInterface = static_cast<IDrawable *> (this);
        addRef();
        return S_OK;
      }
      else if (iid == IID_IDrawable)
      {
        *ppvInterface = static_cast<IDrawable *> (this);
        addRef();
        return S_OK;
      }
      else
      {
        *ppvInterface = nullptr;
        return E_NOINTERFACE;
      }
    }

    virtual uint32_t addRef() noexcept override
    {
      const uint32_t y = ++m_nRefCount;
      std::cout << "addRef => " << m_nRefCount << "\n";
      return y;
    }

    virtual uint32_t release() noexcept override
    {
      const uint32_t y = --m_nRefCount;

      std::cout << "release => " << m_nRefCount << "\n";

      if (y == 0)
        delete this;

      return y;
    }

  private:
    uint32_t m_nRefCount;
  };
}

#endif // CCOM_DEMO_IMPL_CPAPER_HPP

