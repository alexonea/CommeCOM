// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  Copyright 2019 Alexandru N. Onea (alexandru.onea@toporcomputing.com)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#if ! defined(CCOM_IUNKNOWN_HPP)
#define CCOM_IUNKNOWN_HPP 1

#include <CCom/Types.hpp>

namespace CCom
{
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  IUnknown - this is the base interface of all COM objects. Any COM object
  //    must inherit from this class).
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  struct IUnknown
  {
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  queryInterface - takes an interface ID (GUID) and a double pointer to
    //    void, returns RESULT (error code).
    //
    //  Checks whether the interface represented by the required interface ID
    //    (GUID) is implemented by the final objects pointed to by 'this'. If
    //    so, then performs the necessary cast and returns the pointer to the
    //    required interface through the out parameter ppvInterface.
    //
    //  Note: In the process, this method should also call addRef in case of
    //    success, to record the fact that a new reference to 'this' has been
    //    given out. Other components such as CInterfacePtr depend on this
    //    fact.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    virtual
    RESULT
    queryInterface
    (RefIID iid, void **ppvInterface)
    noexcept = 0;

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  addRef - increments and returns the internal reference counter
    //
    //  Note: The reference counter is defined by the final implementation.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    virtual
    uint32_t
    addRef
    ()
    noexcept = 0;

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    //
    //  release - decremetns and returns the internal reference counter. If the
    //    reference counter reached zero, calls delete on the final object.
    //
    //  Note: The reference counter is defined by the final implementation.
    //  Note: Other components such as CInterfacePtr rely on the fact that
    //    this method destructs the final implementation when the reference
    //    count reaches zero.
    //
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    virtual
    uint32_t
    release
    ()
    noexcept = 0;

    template <class IDesired>
    RESULT
    queryInterface
    (RefIID iid, IDesired **ppInterface)
    noexcept
    {
      void *ppvInterface;
      const RESULT res = queryInterface
      (
        iid,
        static_cast <void **> (static_cast <void *> (&ppvInterface))
      );

      *ppInterface = static_cast <IDesired *> (*ppvInterface);
      return res;
    }
  };

} // namespace CCom

CCOM_DEFINE_IID_SYMBOL (IUnknown, 0x00000000, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
CCOM_DEFINE_IID_TRAIT  (CCom::IUnknown, 0x00000000, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#endif // CCOM_IUNKNOWN_HPP
