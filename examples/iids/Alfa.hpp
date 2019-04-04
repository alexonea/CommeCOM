#ifndef ALFA_HPP
#define ALFA_HPP 1


template <typename T>
struct Love
{
  static float x;

};

template <typename T>
float Love <T>::x = 2.7172f;

template <>
inline
float Love <unsigned>::x = 1.4142f;

inline bool b ()
{
  return false;
}

struct Hihi
{
  inline bool f ();
};

#endif
