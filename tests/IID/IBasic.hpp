#if ! defined (CCOM_TESTS_IID_IBASIC_HPP)
#define CCOM_TESTS_IID_IBASIC_HPP 1

#include <CCom/IUnknown.hpp>

namespace CComTests
{

  struct IBasic : public CCom::IUnknown
  {
    virtual
    void
    doBasicStuff
    ()
    noexcept = 0;
  };

} // CComTests

CCOM_DEFINE_IID_NS (CComTests, IBasic, "80000001300000040100000010000000");

#endif // CCOM_TESTS_IID_IBASIC_HPP
