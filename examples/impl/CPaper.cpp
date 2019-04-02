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

#include "impl/CPaper.hpp"

#include <CCom/Dynamic.hpp>

namespace CComExamples
{
  CPaper::CPaper
  ()
  {
    std::cout << "CPaper::CPaper()" << std::endl;
  }

  CPaper::~CPaper
  ()
  {
    std::cout << "CPaper::~CPaper()" << std::endl;
  }

  void
  CPaper::draw()
  noexcept
  {
    std::cout << "CPaper::draw()" << std::endl;
  }

  CCOM_DL_ENTRY_POINT(getInstance, CPaper);
}

