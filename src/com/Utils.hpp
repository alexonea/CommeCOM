#if !defined(EXPERIMENTAL_UTILS_HPP)
#define EXPERIMENTAL_UTILS_HPP 1

namespace HIT
{
  inline
  void **
  toVoidPtrPtr
  (void *pv)
  {
    return static_cast <void **> (pv);
  }
}

#endif // EXPERIMENTAL_UTILS_HPP

