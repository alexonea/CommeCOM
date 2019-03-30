#if !defined(EXPERIMENTAL_COM_TYPES_HPP)
#define EXPERIMENTAL_COM_TYPES_HPP 1

#include <cstdint>

namespace HIT
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
}

#include <com/Guid.hpp>

#endif // EXPERIMENTAL_COM_TYPES_HPP

