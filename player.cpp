#include "player.h"
#include <cmath>
namespace potato_raycasting {

Player::Player(float xx, float yy, float an, uint32_t c, float s)
    : pos{xx, yy}, angle{an}, color{c}, speed{s},
      dir{static_cast<float>(cos(angle)), static_cast<float>(sin(angle))} {}

void Player::move(PlayerControls controls) {
    pos = newPos(controls);
    float nAngle = newAngle(controls);
    if (nAngle != angle) {
        angle = nAngle;
        dir.angle(angle);
    }
}

Vector2 Player::newPos(PlayerControls controls) {
    switch (controls) {
    case potato_raycasting::PlayerControls::up:
        return pos + speed * dir;
    case potato_raycasting::PlayerControls::down:
        return pos - speed * dir;
    default:
        return pos;
    }
}

float Player::newAngle(PlayerControls controls) {
    switch (controls) {
    case potato_raycasting::PlayerControls::right:
        return angle + 0.1;
        break;
    case potato_raycasting::PlayerControls::left:
        return angle - 0.1;
        break;
    default:
        return angle;
    }
}
} // namespace potato_raycasting
