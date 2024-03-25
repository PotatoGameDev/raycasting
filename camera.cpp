#include "camera.h"

namespace potato_raycasting {

Camera::Camera(float x, float y) : _pos{x, y} {};
Camera::Camera(Vector2 pos) : _pos{pos} {};

} // namespace potato_raycasting
