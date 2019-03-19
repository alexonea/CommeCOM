#if !defined(EXPERIMENTAL_IUNKNOWN_HPP)
#define EXPERIMENTAL_IUNKNOWN_HPP 1

#include "com/Guid.hpp"

namespace HIT
{
  struct IUnknown
  {
    virtual int queryInterface(const RefIID iid, void **ppvInterface) = 0;
    virtual int addRef() = 0;
    virtual int release() = 0;
  };
}

extern "C"
{
  const HIT::GUID IID_IUnknown = {
    0x00000000, 0x0000, 0x0000,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 }
  };
}

#endif // EXPERIMENTAL_IUNKNOWN_HPP

