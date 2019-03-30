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

  inline
  bool
  isIUnknown
  (const GUID& iid)
  {
    return (iid.data1    == 0x00000000 &&
            iid.data2    == 0x0000 &&
            iid.data3    == 0x0000 &&
            iid.data4[0] == 0xc0 &&
            iid.data4[1] == 0x00 &&
            iid.data4[2] == 0x00 &&
            iid.data4[3] == 0x00 &&
            iid.data4[4] == 0x00 &&
            iid.data4[5] == 0x00 &&
            iid.data4[6] == 0x00 &&
            iid.data4[7] == 0x46);
  }

  template <class I>
  struct IID_Traits
  {};

  #if defined (CCOM_INSTANTIATE_IID)
    #define CCOM_DEFINE_IID(I, a, b, c, d1, d2, d3, d4, d5, d6, d7, d8) \
      extern "C" \
      const CCom::GUID IID_##I = {a, b, c, {d1, d2, d3, d4, d5, d6, d7, d8}}; \
      \
      template <> \
      struct IID_Traits <I> \
      { \
        static \
        const \
        CCom::GUID \
        iid; \
      }; \
      \
      const \
      CCom::GUID \
      CCom::IID_Traits <I>::iid = {a, b, c, { d1, d2, d3, d4, d5, d6, d7, d8 }};
  #else
   #define CCOM_DEFINE_IID(I, a, b, c, d1, d2, d3, d4, d5, d6, d7, d8) \
      extern "C" \
      const CCom::GUID IID_##I; \
      \
      template <> \
      struct IID_Traits <I> \
      { \
        static \
        const \
        CCom::GUID \
        iid; \
      };
  #endif

} // namespace CCom

#endif // CCOM_GUID_HPP

