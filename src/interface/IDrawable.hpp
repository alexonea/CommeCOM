#if !defined(EXPERIMENT_IDRAWABLE_HPP)
#define EXPERIMENT_IDRAWABLE_HPP 1

namespace HIT
{
  struct IDrawable
  {
    virtual void draw() = 0;
  };

  using DLEntryPointFunc = int (*) (IDrawable **ppInterface);
}

#endif // EXPERIMENT_IDRAWABLE_HPP

