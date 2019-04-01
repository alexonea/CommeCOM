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

#if ! defined(CCOM_DEMO_IMPL_CPAPER_HPP)
#define CCOM_DEMO_IMPL_CPAPER_HPP 1

#define CCOM_INSTANTIATE_IID 1

#include <iostream>

#include <CCom/CComObjectBase.hpp>
#include <interface/IDrawable.hpp>

namespace CComExamples
{
  class CPaper : public CCom::CComObjectBase <CPaper, IDrawable>
  {
  public:
    CPaper();
    ~CPaper();

  public:
    virtual
    void
    draw()
    noexcept override;
  };
}

#endif // CCOM_DEMO_IMPL_CPAPER_HPP

