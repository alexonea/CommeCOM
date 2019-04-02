#include <assert.h>
#include "IBasic.hpp"

int
main ()
{
  const bool bRes = IID_IBasic == CCom::IID_Traits <CComTests::IBasic>::iid;
  assert (bRes);
  return 0;
}

