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

#if ! defined(CCOM_GUID_HPP)
#define CCOM_GUID_HPP 1

#include <cstdint>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace CCom
{
  struct _GUID
  {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t  data4[8];
  };

  using GUID  = boost::uuids::uuid;
  using IID   = GUID;
  using CLSID = GUID;

  using RefIID = const GUID &;

  /*
  inline
  bool
  operator==
  (const GUID &lhs, const GUID &rhs)
  {
    const uint8_t *pLhsData = reinterpret_cast <const uint8_t *> (&lhs);
    const uint8_t *pRhsData = reinterpret_cast <const uint8_t *> (&rhs);

    for (int i = 0; i < sizeof (lhs); ++i)
      if (pLhsData[i] != pRhsData[i])
        return false;

    return true;
  }

  inline
  bool
  operator!=
  (const GUID &lhs, const GUID &rhs)
  {
    return ! (lhs == rhs);
  }
  */

  template <class I>
  struct IID_Traits
  {
    static
    const
    GUID
    iid;
  };

  #define CCOM_DEFINE_IID_TRAIT(I, data) \
    template <> \
    const \
    CCom::GUID \
    CCom::IID_Traits <I>::iid = boost::uuids::string_generator () (data);

  #if defined (CCOM_INSTANTIATE_IID)

    #define CCOM_DEFINE_IID_SYMBOL(I, data) \
      extern "C" \
      const CCom::GUID IID_##I = boost::uuids::string_generator () (data);

    #define CCOM_DEFINE_IID(...) CCOM_DEFINE_IID_TRAIT(__VA_ARGS__)

  #else

    #define CCOM_DEFINE_IID_SYMBOL(I, data) \
      extern "C" \
      const CCom::GUID IID_##I;

    #define CCOM_DEFINE_IID(...) CCOM_DEFINE_IID_TRAIT(__VA_ARGS__)

  #endif

} // namespace CCom

#endif // CCOM_GUID_HPP
