#if !defined(EXPERIMENT_IDRAWABLE_HPP)
#define EXPERIMENT_IDRAWABLE_HPP 1

#include "interface/IUnknown.hpp"
#include <com/CComObject.hpp>

namespace HIT
{
  struct IDrawable : public IUnknown
  {
    virtual void draw() = 0;
  };

  using DLEntryPointFunc = int (*) (IUnknown **ppInterface);
  using DLEntryPointObjectFunc = int (*) (CComObject<IUnknown>& object);

  template <>
  struct IIDTraits<IDrawable>
  {
    static inline constexpr HIT::GUID IID()
    {
      return { 0xAB00CD00, 0x1234, 0x4568,
        { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
    }
  };
}

extern "C"
{
  const HIT::GUID IID_IDrawable = {
    0xAB00CD00, 0x1234, 0x4568,
    { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 }
  };
}

#endif // EXPERIMENT_IDRAWABLE_HPP

