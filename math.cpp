#include "math.h"

namespace potato_raycasting {
Vector2::Vector2(float _x, float _y) : x{_x}, y{_y} {};
Vector2::Vector2(const Vector2 &rhs) : x{rhs.x}, y{rhs.y} {}

Vector2 Vector2::operator+(const Vector2 &other) const {
  return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2 &other) const {
  return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
  return Vector2(x * scalar, y * scalar);
}
Vector2 Vector2::operator/(float scalar) const {
  return Vector2(x / scalar, y / scalar);
}
Vector2 Vector2::operator+(float con) const {
  return Vector2(x + con, y + con);
}
Vector2 Vector2::operator-(float con) const {
  return Vector2(x - con, y - con);
}

Vector2 &Vector2::operator+=(const Vector2 &rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Vector2 &vec) {
  os << "(" << vec.x << "," << vec.y << ")";
  return os;
}
Vector2 operator*(float scalar, const Vector2 &vec) { return vec * scalar; }
Vector2 operator/(float scalar, const Vector2 &vec) { return vec / scalar; }

void Vector2::rotate(float radians) {
  float cr = cos(radians);
  float sr = sin(radians);
  float nx = x * cr - y * sr;
  float ny = x * sr + y * cr;
  x = nx;
  y = ny;
}

void Vector2::angle(float radians) {
  x = sin(radians);
  y = cos(radians);
}

// ========== Ray ==============

Ray::Ray(Vector2 _from, Vector2 _through): from{_from}, through{_through} {}

Ray Ray::operator*(float scalar) const {
  return Ray(from * scalar, through * scalar);
}
Ray Ray::operator/(float scalar) const {
  return Ray(from / scalar, through / scalar);
}

} // namespace potato_raycasting
