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

namespace CCom
{
  struct GUID
  {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t  data4[8];
  };

  using IID   = GUID;
  using CLSID = GUID;

  using RefIID = const GUID &;

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

  template <class I>
  struct IID_Traits
  {
    inline
    static
    const
    GUID
    iid
    ();
  };

  constexpr
  GUID
  fromStr (const char * const p);

  #if defined (__GNUC__) && (__GNUC__ < 7)
    #define CCOM_ENCLOSING_NS_BEGIN namespace CCom {
    #define CCOM_ENCLOSING_NS_END }
    #define CCOM_IID_TRAITS struct IID_Traits
  #else
    #define CCOM_ENCLOSING_NS_BEGIN
    #define CCOM_ENCLOSING_NS_END
    #define CCOM_IID_TRAITS struct CCom::IID_Traits
  #endif

  #define CCOM_DEFINE_IID_TRAIT(I, data) \
    CCOM_ENCLOSING_NS_BEGIN \
    template <> \
    CCOM_IID_TRAITS <I> \
    { \
      inline \
      static \
      constexpr \
      const \
      CCom::GUID \
      iid \
      () \
      { \
        return IID_##I; \
      } \
    }; \
    CCOM_ENCLOSING_NS_END

  #define CCOM_DEFINE_IID_TRAIT_NS(NS, I, data) \
    CCOM_ENCLOSING_NS_BEGIN \
    template <> \
    CCOM_IID_TRAITS <NS::I> \
    { \
      inline \
      static \
      constexpr \
      const \
      CCom::GUID \
      iid \
      () \
      { \
        return IID_##I; \
      } \
    }; \
    CCOM_ENCLOSING_NS_END

  // [2019-04-06] AOnea: is CCOM_INSTANTIATE_IID necessary? We need to consider broader cases.
  #if defined (CCOM_INSTANTIATE_IID)

    #define CCOM_DEFINE_IID_SYMBOL(I, data) \
      static constexpr const CCom::GUID IID_##I = CCom::fromStr (data)

    #define CCOM_DEFINE_IID(...) \
      CCOM_DEFINE_IID_SYMBOL(__VA_ARGS__); \
      CCOM_DEFINE_IID_TRAIT(__VA_ARGS__) \

    #define CCOM_DEFINE_IID_NS(NS, ...) \
      CCOM_DEFINE_IID_SYMBOL(__VA_ARGS__); \
      CCOM_DEFINE_IID_TRAIT_NS(NS, __VA_ARGS__) \

  #else

    #define CCOM_DEFINE_IID_SYMBOL(I, data) \
      static constexpr const CCom::GUID IID_##I = CCom::fromStr (data)

    #define CCOM_DEFINE_IID(...) \
      CCOM_DEFINE_IID_SYMBOL(__VA_ARGS__); \
      CCOM_DEFINE_IID_TRAIT(__VA_ARGS__)

    #define CCOM_DEFINE_IID_NS(NS, ...) \
      CCOM_DEFINE_IID_SYMBOL(__VA_ARGS__); \
      CCOM_DEFINE_IID_TRAIT_NS(NS, __VA_ARGS__) \

  #endif

} // namespace CCom

#include <CCom/Parse.hpp>

#endif // CCOM_GUID_HPP
