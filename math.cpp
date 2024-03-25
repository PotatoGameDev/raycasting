#include "math.h"

namespace potato_raycasting {
Vector2::Vector2(float _x, float _y) : x{_x}, y{_y} {};
Vector2::Vector2(const Vector2& rhs) : x{rhs.x}, y{rhs.y} {}

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

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}
Vector2 operator*(float scalar, const Vector2 &vec) { return vec * scalar; }
Vector2 operator/(float scalar, const Vector2 &vec) { return vec / scalar; }
} // namespace potato_raycasting
