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

#if ! defined(CCOM_DYNAMIC_HPP)
#define CCOM_DYNAMIC_HPP 1

#include <CCom/Types.hpp>
#include <CCom/Utils.hpp>

#include <CCom/CInterfacePtr.hpp>

namespace CCom
{
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  Default entry point signature (used with the default entry point
  //    definition macro below). If this changes, please make sure that the
  //    macro definition stays in sync.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  using DLEntryPointPPVFunc = RESULT(RefIID iid, void **ppvInterface);

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  getInterfacePtr - helper wrapper over the default DLL entry point which
  //    attaches the desired interface pointer to a CIntefacePtr instance.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class IDesired>
  RESULT
  getInterfacePtr
  (DLEntryPointPPVFunc pfnGetInterface, CInterfacePtr <IDesired> &p)
  {
    if (! pfnGetInterface)
      // [2019-03-30]: E_POINTER might be a better choice
      return E_FAIL;
    
    IDesired *pDesired;
    const auto res = pfnGetInterface
    (
      IID_Traits <IDesired>::iid,
      toVoidPtrPtr (&pDesired)
    );

    if (FAILED (res))
      return res;

    p.attach (pDesired);
    return res;
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  CCOM_DL_ENTRY_POINT - macro definition for defining default entry points
  //    for shared objects / plugins using COM-like objects.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  #define CCOM_DL_ENTRY_POINT(FuncName, Instance, args...) \
  extern "C" \
  CCom::RESULT \
  FuncName \
  (CCom::RefIID iid, void **ppvInterface) \
  try \
  { \
    CCom::CInterfacePtr <CCom::IUnknown> p; \
    p.attach (new Instance (args)); \
    const auto res = p->queryInterface (iid, ppvInterface); \
    \
    return res; \
  } \
  catch (...) \
  { \
    *ppvInterface = nullptr; \
    return CCom::E_FAIL; \
  }

} // namespace CCom

#endif // CCOM_DYNAMIC_HPP

