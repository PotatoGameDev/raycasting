#include "camera.h"

namespace potato_raycasting {

Camera::Camera(float radians, float distance)
    : _plane{distance, 0.0}, _dist{distance} {
  _plane.angle(radians + 0.5 * M_PI);
};

void Camera::rotate(float radians) { _plane.rotate(radians + 0.5 * M_PI); }
void Camera::angle(float radians) {
  _plane.x = _dist;
  _plane.y = 0.0;
  _plane.angle(radians + 0.5 * M_PI);
}
Vector2 Camera::start(const Vector2 &playerPos, const Vector2 &playerDir) {
  return (playerPos + playerDir * _dist) - _plane;
}
Vector2 Camera::end(const Vector2 &playerPos, const Vector2 &playerDir) {
  return (playerPos + playerDir * _dist) + _plane;
}
  Ray Camera::ray(const Vector2& playerPos, const Vector2& playerDir, float planeFraction) {
    return {
        playerPos,
        start(playerPos, playerDir) + (planeFraction * 2 * _plane),
    };
  }
} // namespace potato_raycasting
