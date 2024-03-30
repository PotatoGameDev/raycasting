#ifndef POTATO_RAYCASTING_CAMERA_H
#define POTATO_RAYCASTING_CAMERA_H
#include "math.h"

namespace potato_raycasting {

class Camera {
Vector2 _plane;
float _dist;

public:
  Camera(float, float = 1.0);
  
  void angle(float);
  void rotate(float);
  Vector2 start(const Vector2&, const Vector2&);
  Vector2 end(const Vector2&, const Vector2&);
  Ray ray(const Vector2&, const Vector2&, float);
};

} // namespace potato_raycasting
#endif
