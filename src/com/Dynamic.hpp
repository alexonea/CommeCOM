#if !defined(EXPERIMENTAL_DYNAMIC_HPP)
#define EXPERIMENTAL_DYNAMIC_HPP 1

#include <com/Types.hpp>
#include <com/Utils.hpp>

#include <com/CInterfacePtr.hpp>

namespace HIT
{
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  Default entry point signature (used with the default entry point
  //    definition macro below). If this changes, please make sure that the
  //    macro definition stays in sync.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  using DLEntryPointPPVFunc = RESULT(RefIID iid, void **ppvInterface);

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  getInterfacePtr - helper wrapper over the default DLL entry point which
  //    attaches the desired interface pointer to a CIntefacePtr instance.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <class IDesired>
  RESULT
  getInterfacePtr
  (DLEntryPointPPVFunc pfnGetInterface, CInterfacePtr <IDesired> &p)
  {
    if (! pfnGetInterface)
      // [2019-03-30]: E_POINTER might be a better choice
      return E_FAIL;
    
    IDesired *pDesired;
    const auto res = pfnGetInterface
    (
      IID_Traits <IDesired>::iid,
      toVoidPtrPtr (&pDesired)
    );

    if (FAILED (res))
      return res;

    p.attach (pDesired);
    return res;
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  HIT_DL_ENTRY_POINT - macro definition for defining default entry points
  //    for shared objects / plugins using COM-like objects.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  #define HIT_DL_ENTRY_POINT(FuncName, Instance, args...) \
  extern "C" \
  HIT::RESULT \
  FuncName \
  (HIT::RefIID iid, void **ppvInterface) \
  try \
  { \
    HIT::CInterfacePtr <HIT::IUnknown> p; \
    p.attach (new Instance (args)); \
    const auto res = p->queryInterface (iid, ppvInterface); \
    \
    return res; \
  } \
  catch (...) \
  { \
    *ppvInterface = nullptr; \
    return HIT::E_FAIL; \
  }
}

#endif // EXPERIMENTAL_DYNAMIC_HPP

