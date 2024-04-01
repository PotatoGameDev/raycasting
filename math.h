#ifndef POTATO_RAYCASTING_MATH_H
#define POTATO_RAYCASTING_MATH_H
#include <cmath>
#include <iostream>

namespace potato_raycasting {

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Vector2 {
  float x;
  float y;

  Vector2(float, float);
  Vector2(const Vector2 &);
  Vector2 operator+(const Vector2 &) const;
  Vector2 operator-(const Vector2 &) const;
  Vector2 operator+(float) const;
  Vector2 operator-(float) const;
  Vector2 operator*(float) const;
  Vector2 operator/(float) const;
  Vector2 &operator+=(const Vector2 &);
  Vector2 &operator-=(const Vector2 &);

  void rotate(float);
  void angle(float);
  void norm();
  float len();
};

std::ostream &operator<<(std::ostream &, const Vector2 &);
Vector2 operator*(float, const Vector2 &);
Vector2 operator/(float, const Vector2 &);

struct Ray {
  Vector2 from;
  Vector2 through;
  Vector2 dir;

  Ray(Vector2, Vector2);

  Ray operator*(float) const;
  Ray operator/(float) const;
};

} // namespace potato_raycasting
#endif
