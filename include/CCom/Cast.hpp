#if ! defined(CCOM_CAST_HPP)
#define CCOM_CAST_HPP 1

#include <CCom/CInterfacePtr.hpp>

namespace CCom
{
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  interface_cast - cast operation between two CIntefacePtr instances
  //
  //  Thanks to Catalin GCComa for poiting out the necessity of a free function
  //    to perform the cast as opposed to the original conversion constructor
  //    within the CInterfacePtr implementation. In short: interface casting
  //    supports both down and up casts. While down casts are always allowed,
  //    up casts should be made explicit through a cast operation.
  //
  //  Note: the conversion constructor can still be enabled through a define
  //    at compile time. It is now disabled by default.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class IDesired, class ICurrent>
  inline
  CInterfacePtr <IDesired>
  interface_cast
  (const CInterfacePtr <ICurrent> &ptr)
  noexcept
  {
    CInterfacePtr <IDesired> tmp;
    ptr.queryInterface (tmp);

    return tmp;
  }

} // namespace CCom

#endif // CCOM_CAST_HPP
