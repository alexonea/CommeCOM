// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  Copyright 2019 Alexandru N. Onea (alexandru.onea@toporcomputing.com)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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
