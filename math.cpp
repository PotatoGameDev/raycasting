#include "math.h"
#include <cmath>

namespace potato_raycasting {
Vector2::Vector2(float _x, float _y) : x{_x}, y{_y} {};
Vector2::Vector2(int _x, int _y) : x{static_cast<float>(_x)}, y{static_cast<float>(_y)} {};
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

float Vector2::dot(const Vector2& other) {
    return x * other.x + y * other.y;
}

float Vector2::len() const { return std::sqrt(x * x + y * y); }

void Vector2::norm() {
  float invLen = 1 / this->len();
  x *= invLen;
  y *= invLen;
}

Vector2 Vector2::normalized() const {
  float invLen = 1 / this->len();
  return Vector2(x * invLen, y * invLen);
}

float Vector2::dist(const Vector2 &other) const {
    return (other - *this).len();
}

std::ostream &operator<<(std::ostream &os, const Vector2 &vec) {
  os << "(" << vec.x << "," << vec.y << ")";
  return os;
}
Vector2 operator*(float scalar, const Vector2 &vec) { return vec * scalar; }
Vector2 operator/(float scalar, const Vector2 &vec) { return vec / scalar; }

// This uses counterclockwise rotation matrics:
// x' =  x*cos(θ) - y*sin(θ)
// y' =  x*sin(θ) + y*cos(θ)
// But produces clockwise rotation, because the matrix is for freeckin standard Carthesian
// coodinate system, and this math lib works with y-down, x-right system.
void Vector2::rotate(float radians) {
  float cr = cos(radians);
  float sr = sin(radians);
  float nx = x * cr - y * sr;
  float ny = x * sr + y * cr;
  x = nx;
  y = ny;
}

void Vector2::angle(float radians) {
    float len = this->len();
    x = len * cos(radians);
    y = len * sin(radians);
}

// =============================
// ========== Ray ==============

Ray::Ray(Vector2 _from, Vector2 _through)
    : from{_from}, through{_through}, dir{through - from} {
  dir.norm();
}

Ray Ray::operator*(float scalar) const {
  return Ray(from * scalar, through * scalar);
}
Ray Ray::operator/(float scalar) const {
  return Ray(from / scalar, through / scalar);
}

// =============================
// ======== RayHit =============

RayHit::RayHit(int _type, int _side, float _dist)
    : type{_type}, side{_side}, dist{_dist} {}

// =============================
} // namespace potato_raycasting
