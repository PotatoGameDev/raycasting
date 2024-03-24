#include "player.h"
#include <iostream>
namespace potato_raycasting {

Player::Player(float xx, float yy, uint32_t c, float s): x{xx}, y{yy}, color{c}, speed{s} { }

void Player::move(PlayerControls controls) {
    switch (controls) {
        case potato_raycasting::PlayerControls::east:
            std::cout << controls << " " << speed << std::endl;
            x += speed;
            break;
        case potato_raycasting::PlayerControls::west:
            std::cout << controls << " " << speed << std::endl;
            x -= speed;
            break;
        case potato_raycasting::PlayerControls::north:
            std::cout << controls << " " << speed << std::endl;
            y -= speed;
            break;
        case potato_raycasting::PlayerControls::south:
            std::cout << controls << " " << speed << std::endl;
            y += speed;
            break;
    }
}
} // namespace potato_raycasting



















