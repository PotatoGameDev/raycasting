#ifndef POTATO_RAYCASTING_CAMERA_H
#define POTATO_RAYCASTING_CAMERA_H
#include "player.h"
#include "math.h"

namespace potato_raycasting {

class Camera {
Vector2 _pos;

public:
  Camera(float, float);
  Camera(Vector2);
  

};

} // namespace potato_raycasting
#endif
