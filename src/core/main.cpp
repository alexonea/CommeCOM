#include <iostream>
#include <dlfcn.h>

#define HIT_INSTANTIATE_IID 1

#include <interface/IDrawable.hpp>

#include <com/IUnknown.hpp>
#include <com/CInterfacePtr.hpp>
#include <com/Dynamic.hpp>
#include <com/Cast.hpp>

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

  dll::shared_library impl (argv[1]);
  auto pfnGetInterface = impl.get <HIT::DLEntryPointPPVFunc> ("getInstance");
  
  if (! pfnGetInterface)
  {
    std::cerr << "[main] could not get entry point symbol" << std::endl;
    return 1;
  }

  try
  {
    HIT::CInterfacePtr <HIT::IDrawable> pDrawable;
    HIT::getInterfacePtr (pfnGetInterface, pDrawable);

    if (pDrawable)
      pDrawable->draw();
    else
      std::cerr << "[main] could not acquire IDrawable, going on...\n";
    
    auto pUnknown = HIT::interface_cast <HIT::IUnknown> (pDrawable);
    if (pUnknown)
    {
      auto pTest = HIT::interface_cast <HIT::IDrawable> (pUnknown);
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

