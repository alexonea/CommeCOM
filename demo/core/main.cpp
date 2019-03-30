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

  dll::shared_library impl (argv[1]);
  auto pfnGetInterface = impl.get <CCom::DLEntryPointPPVFunc> ("getInstance");
  
  if (! pfnGetInterface)
  {
    std::cerr << "[main] could not get entry point symbol" << std::endl;
    return 1;
  }

  try
  {
    CCom::CInterfacePtr <CCom::IDrawable> pDrawable;
    CCom::getInterfacePtr (pfnGetInterface, pDrawable);

    if (pDrawable)
      pDrawable->draw();
    else
      std::cerr << "[main] could not acquire IDrawable, going on...\n";
    
    auto pUnknown = CCom::interface_cast <CCom::IUnknown> (pDrawable);
    if (pUnknown)
    {
      auto pTest = CCom::interface_cast <CCom::IDrawable> (pUnknown);
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

