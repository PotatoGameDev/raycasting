#include "player.h"
#include <cmath>
namespace potato_raycasting {

Player::Player(float xx, float yy, float an, uint32_t c, float s)
    : pos{xx, yy}, angle{an}, color{c}, speed{s},
      dir{static_cast<float>(cos(angle)), static_cast<float>(sin(angle))} {
      }

void Player::move(PlayerControls controls) {
  switch (controls) {
  case potato_raycasting::PlayerControls::right:
    angle += 0.1;
    dir.angle(angle);
    break;
  case potato_raycasting::PlayerControls::left:
    angle -= 0.1;
    dir.angle(angle);
    break;
  case potato_raycasting::PlayerControls::up:
    pos += speed * dir;
    break;
  case potato_raycasting::PlayerControls::down:
    pos -= speed * dir;
    break;
  }
}
} // namespace potato_raycasting
