#include <assert.h>
#include "IBasic.hpp"

#include <CCom/Parse.hpp>

#include <cstring>

constexpr CCom::_GUID ref =
{
  0x11223344,
  0x5566,
  0x7788,
  {
    0x99,
    0x00,
    0xAA,
    0xBB,
    0xCC,
    0xDD,
    0xEE,
    0xFF
  }
};

constexpr CCom::_GUID test1 = CCom::fromStr ("11223344556677889900AABBCCDDEEFF");
constexpr CCom::_GUID test2 = CCom::fromStr ("1122334455-667-78-8-9900AABBCCDDEEFF");
constexpr CCom::_GUID test3 = CCom::fromStr ("{1122334455-667-78-8-9900AABBCCDDEEFF}");
constexpr CCom::_GUID test4 = CCom::fromStr ("---1122334455-667-78-8-9900AABBCCDDEEFF--");
constexpr CCom::_GUID test5 = CCom::fromStr ("1122334455-667-78-8-9900AABBCCDDEEFFABC");

int
main ()
{
  const bool bRes = IID_IBasic == CCom::IID_Traits <CComTests::IBasic>::iid ();
  assert (bRes);
  
  assert (! memcmp (&test1, &ref, sizeof (CCom::_GUID)));
  assert (! memcmp (&test2, &ref, sizeof (CCom::_GUID)));
  assert (! memcmp (&test3, &ref, sizeof (CCom::_GUID)));
  assert (! memcmp (&test4, &ref, sizeof (CCom::_GUID)));
  assert (! memcmp (&test5, &ref, sizeof (CCom::_GUID)));

  return 0;
}

