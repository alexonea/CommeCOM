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

#define CCOM_INSTANTIATE_IID 1

#include <iostream>

#include <CCom/CInterfacePtr.hpp>
#include <CCom/Dynamic.hpp>

#include <interface/IDrawable.hpp>

#include <boost/dll.hpp>

int
main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    std::cout << "One argument is required: the shared object" << std::endl;
    return 1;
  }

  std::cout << "Loading " << argv[1] << " ..." << std::endl;

  namespace dll = boost::dll;
  using namespace CComExamples;

  dll::shared_library impl (argv[1]);
  auto pfnGetInterface = impl.get <CCom::DLEntryPointPPVFunc> ("getInstance");

  if (! pfnGetInterface)
  {
    std::cerr << "[main] could not get entry point symbol" << std::endl;
    return 1;
  }

  try
  {
    CCom::CInterfacePtr <IDrawable> pDrawable;
    CCom::getInterfacePtr (pfnGetInterface, pDrawable);

    if (pDrawable)
      pDrawable->draw();
    else
      std::cerr << "[main] could not acquire IDrawable, going on...\n";

    auto pUnknown = CCom::interface_cast <CCom::IUnknown> (pDrawable);
    if (pUnknown)
    {
      auto pTest = CCom::interface_cast <IDrawable> (pUnknown);
      if (pTest)
        pTest->draw();
    }
  }
  catch (...)
  {
    std::cerr << "catstrophe" << std::endl;
  }

  return 0;
}

