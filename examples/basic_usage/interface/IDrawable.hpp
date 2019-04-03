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

#if ! defined(CCOM_DEMO_INTERFACE_IDRAWABLE_HPP)
#define CCOM_DEMO_INTERFACE_IDRAWABLE_HPP 1

#include <CCom/IUnknown.hpp>

namespace CComExamples
{
  struct IDrawable : public CCom::IUnknown
  {
    virtual
    void
    draw
    ()
    noexcept = 0;
  };
}

CCOM_DEFINE_IID (CComExamples::IDrawable, 0xAB00CD00, 0x1234, 0x4568, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


#endif // CCOM_DEMO_INTERFACE_IDRAWABLE_HPP

