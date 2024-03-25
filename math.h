#ifndef POTATO_RAYCASTING_MATH_H
#define POTATO_RAYCASTING_MATH_H
#include <iostream>

namespace potato_raycasting {

struct Vector2 {
  float x;
  float y;

  Vector2(float, float);
  Vector2(const Vector2&);
  Vector2 operator+(const Vector2 &) const;
  Vector2 operator-(const Vector2 &) const;
  Vector2 operator*(float) const;
  Vector2 operator/(float) const;
  Vector2& operator+=(const Vector2&);
  Vector2& operator-=(const Vector2&);

};

std::ostream& operator<<(std::ostream&, const Vector2&);
Vector2 operator*(float, const Vector2&);
Vector2 operator/(float, const Vector2&);

} // namespace potato_raycasting
#endif
