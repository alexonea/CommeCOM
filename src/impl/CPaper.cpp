#include "impl/CPaper.hpp"

#include <com/CComObject.hpp>

#include <algorithm>

namespace HIT
{
  void
  CPaper::draw()
  {
    std::cout << "CPaper::draw()" << std::endl;
  }
}

extern "C"
{
  int getInterface(HIT::IUnknown **ppInterface)
  {
    try
    {
      *ppInterface = new HIT::CPaper();
      return 0;
    }
    catch(...)
    {
      *ppInterface = nullptr;
      return -1;
    }
  }

  int getInterfaceObject(HIT::CComObject<HIT::IUnknown>& object)
  {
    try
    {
      HIT::CComObject<HIT::IUnknown> tmp(new HIT::CPaper());
      std::cout << "before swap\n";
      object.swap(std::move(tmp));
    }
    catch(...)
    {
      return -1;
    }
  }
}

