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
