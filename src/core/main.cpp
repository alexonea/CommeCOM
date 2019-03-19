#include <iostream>
#include <dlfcn.h>

#include <interface/IDrawable.hpp>
#include <interface/IUnknown.hpp>

#include <com/CComObject.hpp>

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

#if 0
  const HIT::DLEntryPointFunc pGetInterface = 
    reinterpret_cast<const HIT::DLEntryPointFunc> (dlsym(hdl, "getInterface"));
  
  if (! pGetInterface)
  {
    std::cerr << "[main]" << dlerror() << std::endl;
    dlclose(hdl);
    return 1;
  }

  HIT::IUnknown *pUnknown;
  {
    const int iRes = pGetInterface(&pUnknown);

    if (iRes != 0 || ! pUnknown)
    {
      std::cerr << "[main] could not acquire interface" << std::endl;
      dlclose(hdl);
      return 1;
    }
  }

  HIT::IDrawable *pDrawable;
  {
    const int iRes = pUnknown->queryInterface(IID_IDrawable,
      (void **) &pDrawable);

    if (iRes != 0 || ! pDrawable)
    {
      std::cerr << "[main] could not acquire interface" << std::endl;
      pUnknown->release();
      dlclose(hdl);
      return 1;
    }
  }


  pDrawable->draw();

  pDrawable->release();
  pUnknown->release();
#endif

#if 1
  const auto pGetInterface = 
    reinterpret_cast<const HIT::DLEntryPointObjectFunc> (
      dlsym(hdl, "getInterfaceObject")
    );
  
  if (! pGetInterface)
  {
    std::cerr << "[main]" << dlerror() << std::endl;
    dlclose(hdl);
    return 1;
  }

  {
    HIT::CComObject<HIT::IUnknown> object;
    {
      const int iRes = pGetInterface(object);

      if (iRes != 0)
      {
        std::cerr << "[main] could not acquire interface" << std::endl;
        dlclose(hdl);
        return 1;
      }
    }

    HIT::CComObject<HIT::IDrawable> pDrawable{object};
    pDrawable->draw();

    HIT::CComObject<HIT::IUnknown> pOther{pDrawable};
  }
#endif

  // pDrawable->release();
  // pUnknown->release();
  dlclose(hdl);
  return 0;
}

