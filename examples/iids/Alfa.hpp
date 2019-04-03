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
float Love <unsigned>::x = 1.4142f;


#endif
