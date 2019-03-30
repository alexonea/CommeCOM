#if !defined(EXPERIMENT_IDRAWABLE_HPP)
#define EXPERIMENT_IDRAWABLE_HPP 1

#include <com/IUnknown.hpp>

namespace HIT
{
  struct IDrawable : public IUnknown
  {
    virtual
    void
    draw
    ()
    noexcept = 0;
  };

  HIT_DEFINE_IID (IDrawable, 0xAB00CD00, 0x1234, 0x4568, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
}

#endif // EXPERIMENT_IDRAWABLE_HPP

