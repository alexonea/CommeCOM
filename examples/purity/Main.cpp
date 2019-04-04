#include <iostream>
#include <sstream>
#include <iomanip>

#include <stdint.h>

struct GUID
{
  uint32_t a [4];
};

std::ostream &operator<< (std::ostream &os, const GUID &guid)
{
  std::ostringstream osTmp;
  {
    osTmp << std::hex << std::uppercase << std::setfill ('0');
    for (std::size_t i = 0; i < 4; ++i)
      osTmp << std::setw (8) << guid.a [i];
  }

  return os << osTmp.str ();
}


template <std::size_t N>
constexpr
const char *
EliminateHyphens
(const char (&a) [N])
{
  char y [N] = {0};

  std::size_t j = 0;
  for (std::size_t i = 0; i < N; ++i)
    if (a [i] == '-')
      continue;
    else
    if (a [i] >= '0' && a [i] <= '9' || a [i] >= 'A' && a [i] <= 'F' || a [i] >= 'a' && a [i] <= 'f')
      y [j++] = a [i];
    else
    if (! a [i])
      break;

  return y;
}

//constexpr unsigned PurelyHexCharToBin4 (char c)
//{
//  return c >= '0' && c <= '9' ? c - '0' : c >= 'A' && c <= 'F' ? c - 'A' + 10 : c >= 'a' && c <= 'f' ? c - 'a' + 10 : -1;
//}

template <char C> unsigned f ();

template <>       unsigned f <'0'> () { return  0; }
template <>       unsigned f <'1'> () { return  1; }
template <>       unsigned f <'2'> () { return  2; }
template <>       unsigned f <'3'> () { return  3; }
template <>       unsigned f <'4'> () { return  4; }
template <>       unsigned f <'5'> () { return  5; }
template <>       unsigned f <'6'> () { return  6; }
template <>       unsigned f <'7'> () { return  7; }
template <>       unsigned f <'8'> () { return  8; }
template <>       unsigned f <'9'> () { return  9; }

template <>       unsigned f <'A'> () { return 10; }
template <>       unsigned f <'B'> () { return 11; }
template <>       unsigned f <'C'> () { return 12; }
template <>       unsigned f <'D'> () { return 13; }
template <>       unsigned f <'E'> () { return 14; }
template <>       unsigned f <'F'> () { return 15; }

template <>       unsigned f <'a'> () { return 10; }
template <>       unsigned f <'b'> () { return 11; }
template <>       unsigned f <'c'> () { return 12; }
template <>       unsigned f <'d'> () { return 13; }
template <>       unsigned f <'e'> () { return 14; }
template <>       unsigned f <'f'> () { return 15; }

#include <stdexcept>
#include <string>
#include <cassert>


constexpr uint64_t f (char c)
{
  return c >= '0' && c <= '9' ? c - '0' : c >= 'A' && c <= 'F' ? c - 'A' + 10 : c >= 'a' && c <= 'f' ? c - 'a' + 10 : -1;
}
/*
template <std::size_t x = 0>
constexpr
uint64_t
fallback
()
{
  static_assert (false, "Incomplete GUID !");
  return 0;
}
*/

constexpr
uint64_t
fone(const char *p, bool bHalf = true, std::size_t current = 1)
{
  using namespace std::string_literals;
  return
    *p == 0 ? (current == 17 ? 0 : throw std::logic_error {"Incomplete GUID"s}) :
    (current == 17 ? (bHalf ? 0 : fone (p, ! bHalf, 1)) :
    (*p == '-' ? fone (p + 1, bHalf, current) : fone (p + 1, bHalf, current + 1) | (f (p[0]) << ((16 - current) * 4))));
}

/*
constexpr
const char *
skip
(const char *p, int &n)
{
  return *p == '-' ? skip (p + 1, ++n) : p;
}

constexpr
uint8_t
parse_hex_u8
(const char *p, int &n)
{
  return f ( skip (p, n) [0]) << 4 | f ( skip (p, 0) [++n]);
}

*/

constexpr uint64_t test = fone ("11223344556677889900AABBCCDDEEFF", false);

int
main()
{
  std::cout << std::hex << std::uppercase << uint64_t (test) << '\n';
}










//template <std::size_t N>
//constexpr
//unsigned g (const char (&p) [N])
//{
//  return f (p [0]);
//}




constexpr
uint8_t h8 (const char *p)
{
  return f (p [0]) << 4 | f (p [1]);
}

constexpr
const char *Skip (const char *p)
{
  return p [0] == '-' ? Skip (p + 1) : p;
}

constexpr
uint16_t h16 (const char *p)
{
  const char *const p0 = Skip (p);
  const uint8_t b0 = h8 (p0);

  const char *const p1 = Skip (p0 + 2);
  const uint8_t b1 = h8 (p1);

  return b0 << 8 | b1;
}

constexpr
uint32_t h32 (const char *p)
{
  const char *const p0 = Skip (p);
  const uint16_t w0 = h8 (p0);

  const char *const p1 = Skip (p0 + 4);
  const uint8_t w1 = h8 (p1);

  return w0 << 16 | w1;
}


/*
int main ()
{
  //constexpr const char q [] = "AAA";
  std::cout << std::hex << std::uppercase << unsigned (h32 ("----------AA-----CC")) << "\n";
}

*/


/*
constexpr uint8_t PurelyHexStringToBin8 (const char *p)
{
  return uint8_t (PurelyHexCharToBin4 (p [0]) << 4 | PurelyHexCharToBin4 (p [1]));
};

constexpr uint16_t PurelyHexStringToBin16 (const char *p)
{
  return uint16_t (PurelyHexStringToBin8 (p + 0) << 8 | PurelyHexStringToBin8 (p + 2));
};

constexpr uint32_t PurelyHexStringToBin32 (const char *p)
{
  return uint32_t (PurelyHexStringToBin16 (p + 0) << 16 | PurelyHexStringToBin16 (p + 4));
};


constexpr GUID PurelyMakeGUID (const char *p)
{
  //GUID guid =
  return
  {
    PurelyHexStringToBin32 (p +  0),
    PurelyHexStringToBin32 (p +  8),
    PurelyHexStringToBin32 (p + 16),
    PurelyHexStringToBin32 (p + 24)
  };

  //guid.a [0] *= 3;

  //return guid;
}


constexpr const char        psz0 [] = "00112233-4455-6677-8899AABBCCDDEEFF";
constexpr const char *const psz1    = EliminateHyphens (psz0);

constexpr GUID guid = PurelyMakeGUID (psz0);







unsigned Oldie (unsigned x)
{
  return x + 1;
}

constexpr
unsigned f (unsigned x)
{
  return x + 1;
}

constexpr unsigned y = f (10);

int main ()
{
  std::cout << guid << '\n';
  return y;
}
*/
