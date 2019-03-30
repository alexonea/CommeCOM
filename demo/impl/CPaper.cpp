#include "impl/CPaper.hpp"

#include <CCom/Dynamic.hpp>

namespace CCom
{
  void
  CPaper::draw()
  noexcept
  {
    std::cout << "CPaper::draw()" << std::endl;
  }

  CCOM_DL_ENTRY_POINT(getInstance, CPaper);
}

