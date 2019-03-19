#include <iostream>
#include <dlfcn.h>

#include <interface/IDrawable.hpp>

int
main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    std::cout << "One argument is required: the shared object" << std::endl;
    return 1;
  }

  std::cout << "Loading " << argv[1] << " ..." << std::endl;
  
  const auto hdl = dlopen(argv[1], RTLD_LAZY);
  if (hdl == nullptr)
  {
    std::cerr << "[main]" << dlerror() << std::endl;
    return 1;
  }

  const HIT::DLEntryPointFunc pGetInterface = 
    reinterpret_cast<const HIT::DLEntryPointFunc> (dlsym(hdl, "getInterface"));
  
  if (! pGetInterface)
  {
    std::cerr << "[main]" << dlerror() << std::endl;
    dlclose(hdl);
    return 1;
  }

  HIT::IDrawable *pDrawable;
  const int iRes = pGetInterface(&pDrawable);

  if (iRes != 0 || ! pDrawable)
  {
    std::cerr << "[main] could not acquire interface" << std::endl;
    dlclose(hdl);
    return 1;
  }

  pDrawable->draw();

  dlclose(hdl);
  return 0;
}

