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

CCOM_DEFINE_IID (CComTests::IBasic, 0x80000001, 0x3000, 0x0004, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00);
CCOM_DEFINE_IID_SYMBOL (IBasic, 0x80000001, 0x3000, 0x0004, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00);

#endif // CCOM_TESTS_IID_IBASIC_HPP

