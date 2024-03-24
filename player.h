#ifndef POTATO_RAYCASTING_PLAYER_H
#define POTATO_RAYCASTING_PLAYER_H
#include "screen.h"

namespace potato_raycasting {

enum PlayerControls { east, west, north, south };

struct Player {
  float x;
  float y;
  float speed;
  uint32_t color;

  Player(float, float, uint32_t, float = 1);

  void move(PlayerControls);
};

} // namespace potato_raycasting

#endif
