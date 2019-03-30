#if ! defined(CCOM_DEMO_IMPL_CPAPER_HPP)
#define CCOM_DEMO_IMPL_CPAPER_HPP 1

#define CCOM_INSTANTIATE_IID 1

#include <iostream>

#include <CCom/Types.hpp>
#include <CCom/CComObjectBase.hpp>

#include <interface/IDrawable.hpp>

namespace CCom
{
  class CPaper : public CComObjectBase <CPaper, IDrawable>
  {
  public:
    CPaper()
    {
      std::cout << "CPaper::CPaper()" << std::endl;
    }

    ~CPaper()
    {
      std::cout << "CPaper::~CPaper()" << std::endl;
    }

  public:
    virtual void draw() noexcept override;
  };
}

#endif // CCOM_DEMO_IMPL_CPAPER_HPP

