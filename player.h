#ifndef POTATO_RAYCASTING_PLAYER_H
#define POTATO_RAYCASTING_PLAYER_H
#include "math.h"
#include "screen.h"

namespace potato_raycasting {

enum PlayerControls { left, right, up, down };

struct Player {
  Vector2 pos;
  float speed;
  uint32_t color;
  float angle; // angle in radians
  Vector2 dir;

  Player(float, float, float, uint32_t, float = 1);
  Player(Vector2, float, uint32_t, float = 1);

  void move(PlayerControls);
};

} // namespace potato_raycasting

#endif
