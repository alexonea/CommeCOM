#include "impl/CPaper.hpp"

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
}

