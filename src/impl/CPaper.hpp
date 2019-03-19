#if !defined(EXPERIMENT_CPAPER_HPP)
#define EXPERIMENT_CPAPER_HPP 1

#include "interface/IDrawable.hpp"

namespace HIT
{
  class CPaper : public IDrawable
  {
    virtual void draw() override;
  };
}

#endif // EXPERIMENT_CPAPER_HPP

