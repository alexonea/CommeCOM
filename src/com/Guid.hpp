#if !defined(EXPERIMENTAL_GUID_HPP)
#define EXPERIMENTAL_GUID_HPP 1

#include <cstdint>

namespace HIT
{
  struct GUID
  {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t  data4[8];
  };

  template <typename I>
  struct IIDTraits
  {
    static inline constexpr GUID IID()
    {
      return { 0 };
    }
  };

  using RefIID = const GUID&;

  inline
  bool
  operator==(const GUID& lhs, const GUID& rhs)
  {
    const uint8_t *pLhsData = reinterpret_cast<const uint8_t *> (&lhs);
    const uint8_t *pRhsData = reinterpret_cast<const uint8_t *> (&rhs);

    for (int i = 0; i < sizeof(lhs); ++i)
      if (pLhsData[i] != pRhsData[i])
        return false;
    
    return true;
  }

  inline
  bool
  operator!=(const GUID& lhs, const GUID& rhs)
  {
    return ! (lhs == rhs);
  }

  inline
  bool
  isIUnknown(const GUID& iid)
  {
    return (iid.data1    == 0x00000000 &&
            iid.data2    == 0x0000 &&
            iid.data3    == 0x0000 &&
            iid.data4[0] == 0x00 &&
            iid.data4[1] == 0x00 &&
            iid.data4[2] == 0x00 &&
            iid.data4[3] == 0x00 &&
            iid.data4[4] == 0x00 &&
            iid.data4[5] == 0x00 &&
            iid.data4[6] == 0x00 &&
            iid.data4[7] == 0x46);
  }
}

#endif // EXPERIMENTAL_GUID_HPP

