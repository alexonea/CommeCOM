#include "impl/CPaper.hpp"

#include <iostream>

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
  int getInterface(HIT::IDrawable **ppInterface)
  {
    try
    {
      *ppInterface = new HIT::CPaper();
      return 0;
    }
    catch(...)
    {
      return -1;
    }
  }
}

