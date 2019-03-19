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

#if !defined (CCOM_PARSE_HPP)
#define CCOM_PARSE_HPP 1

#include <cstdint>
#include <string>
#include <stdexcept>

#include <CCom/Guid.hpp>

namespace CCom
{

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  Macros for compile-time error reporting during the GUID parsing
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  #define CCOM_STATIC_ASSERT(check, msg) \
    (check) ? void (0) : [] { static_assert (! #check, msg); } ()

  #define CCOM_STATIC_THROW(msg) \
    throw std::logic_error { msg }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  __ngroups - Returns the max number of groups (i.e. printable characters)
  //    required to represent in hex a value of type T.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <typename T>
  inline
  constexpr
  std::size_t
  __nGroups
  ()
  {
    return 2 * sizeof (T);
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  __parseU8 - Takes a single character and returns the binary value that
  //    the respective character represents.
  //
  //  In case of an illegal character (not a valid hex character), return a
  //    compile-time error (hopefully).
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  inline
  constexpr
  uint64_t
  __parseU8 (uint8_t c)
  {
    return
        c >= '0' && c <= '9' ? c - '0'
      : c >= 'A' && c <= 'F' ? c - 'A' + 10
      : c >= 'a' && c <= 'f' ? c - 'a' + 10

      : CCOM_STATIC_THROW ("Malformed GUID - illegal character");
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  __compute - Computes a value of type T based on the current 4-bit group
  //    at position pos and the rest of the binary representation of T.
  //
  //  It assumes the following layout:
  //  +--- ~ ---+-----+-----+-----+- ~ -+-----+-----+
  //  |   ???   | lhs |            rest             |
  //  +--- ~ ---+-----+-----+-----+- ~ -+-----+-----+
  //             4-bit      (pos - 1) x 4-bit
  //              ^
  //             pos
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <typename T>
  inline
  constexpr
  T
  __compute
  (std::size_t pos, uint64_t lhs, T rest)
  {
    // static_assert (pos < __nGroups <T> ());
    return (lhs << (__nGroups <T> () - pos - 1) * 4) | rest;
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  __parseNext - parses the next group of type T from the string sequence
  //    skipping the first skip valid groups and starting at position pos.
  //
  //  Returns the parsed value, or reports a compile-time error if can't do so
  //    either because if illegal characters or incomplete GUID.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  template <typename T>
  inline
  constexpr
  T
  __parseNext
  (const char * const p, std::size_t skip = 0, std::size_t pos = 0)
  {
    return 
        pos == __nGroups <T> () ? 0
      : *p == 0                 ? CCOM_STATIC_THROW ("Incomplete GUID")
      : *p == '{' && pos == 0   ? __parseNext <T> (p + 1, skip, pos)
      : *p == '-'               ? __parseNext <T> (p + 1, skip, pos)
      : skip > 0                ? __parseNext <T> (p + 1, skip - 1, pos)
      : __compute <T> (pos, __parseU8 (p[0]), __parseNext <T> (p + 1, skip, pos + 1));
      // : (f (p[0]) << ((numOfGroups <T> () - pos - 1) * 4)) | __parseNext <T> (p + 1, skip, pos + 1);
  }

  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //
  //  fromStr - Parse a string representation of a GUID into an actual GUID
  //
  //  It generates each field of the GUID by parsing the sequence and skipping
  //    a number of groups equal to the offset of GUID field in the string
  //    representation.
  //
  //  Note: Because only legal GUID data groups are skipped (and not hyphens
  //    or other non-data characters), we can effectively give relevant offsets
  //    to any of the GUID data groups.
  //
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  inline
  constexpr
  GUID
  fromStr
  (const char * const p)
  {
    return
    {
      __parseNext <uint32_t> (p),
      __parseNext <uint16_t> (p, 8),
      __parseNext <uint16_t> (p, 8 + 4),
      {
        __parseNext <uint8_t> (p, 8 + 4 + 4),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 2),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 4),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 6),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 8),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 10),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 12),
        __parseNext <uint8_t> (p, 8 + 4 + 4 + 14),
      }
    };
  }
}

#endif // CCOM_PARSE_HPP
