#include "impl/CPaper.hpp"

#include <CCom/Dynamic.hpp>

namespace CCom
{
  CPaper::CPaper
  ()
  {
    std::cout << "CPaper::CPaper()" << std::endl;
  }

  CPaper::~CPaper
  ()
  {
    std::cout << "CPaper::~CPaper()" << std::endl;
  }

  void
  CPaper::draw()
  noexcept
  {
    std::cout << "CPaper::draw()" << std::endl;
  }

  CCOM_DL_ENTRY_POINT(getInstance, CPaper);
}

