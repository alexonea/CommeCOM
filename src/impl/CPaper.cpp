#include "impl/CPaper.hpp"

#include <com/Dynamic.hpp>

namespace HIT
{
  void
  CPaper::draw()
  noexcept
  {
    std::cout << "CPaper::draw()" << std::endl;
  }

  HIT_DL_ENTRY_POINT(getInstance, CPaper);
}

