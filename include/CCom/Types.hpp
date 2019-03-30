#if ! defined(CCOM_TYPES_HPP)
#define CCOM_TYPES_HPP 1

#include <cstdint>

namespace CCom
{
  enum RESULT : int32_t
  {
    S_OK          = int32_t (0x00000000),
    S_FALSE       = int32_t (0x00000001),
    E_NOINTERFACE = int32_t (0x80004002),
    E_FAIL        = int32_t (0x80004005),
    E_OUTOFMEMORY = int32_t (0x8007000e),
  };

  inline bool SUCCEEDED (RESULT r) { return r >= 0;          }
  inline bool FAILED    (RESULT r) { return ! SUCCEEDED (r); }

} // namespace CCom

#include <CCom/Guid.hpp>
#include <CCom/IUnknown.hpp>

#endif // CCOM_TYPES_HPP

