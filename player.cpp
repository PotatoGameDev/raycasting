#include "player.h"
#include <cmath>
#include <iostream>
namespace potato_raycasting {

Player::Player(float xx, float yy, float an, uint32_t c, float s)
    : pos{xx, yy}, angle{an}, color{c}, speed{s},
      dir{static_cast<float>(sin(angle)), static_cast<float>(cos(angle))} {}

void Player::move(PlayerControls controls) {
  Vector2 posa{pos};
  switch (controls) {
  case potato_raycasting::PlayerControls::right:
    angle += 0.1;
    dir.x = sin(angle);
    dir.y = cos(angle);
    break;
  case potato_raycasting::PlayerControls::left:
    angle -= 0.1;
    dir.x = sin(angle);
    dir.y = cos(angle);
    break;
  case potato_raycasting::PlayerControls::up:
    pos += speed * dir;
    break;
  case potato_raycasting::PlayerControls::down:
    pos -= speed * dir;
    break;
  }
  std::cout << " b: " << posa << " a: " << pos << std::endl;
}
} // namespace potato_raycasting
