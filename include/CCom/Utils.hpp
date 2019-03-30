#if ! defined(CCOM_UTILS_HPP)
#define CCOM_UTILS_HPP 1

namespace CCom
{
  inline
  void **
  toVoidPtrPtr
  (void *pv)
  {
    return static_cast <void **> (pv);
  }

} // namespace CCom

#endif // CCOM_UTILS_HPP

