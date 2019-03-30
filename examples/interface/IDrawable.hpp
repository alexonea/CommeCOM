#if ! defined(CCOM_DEMO_INTERFACE_IDRAWABLE_HPP)
#define CCOM_DEMO_INTERFACE_IDRAWABLE_HPP 1

#include <CCom/IUnknown.hpp>

namespace CCom
{
  struct IDrawable : public IUnknown
  {
    virtual
    void
    draw
    ()
    noexcept = 0;
  };

  CCOM_DEFINE_IID (IDrawable, 0xAB00CD00, 0x1234, 0x4568, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
}

#endif // CCOM_DEMO_INTERFACE_IDRAWABLE_HPP

