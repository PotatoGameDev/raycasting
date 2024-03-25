#include "world.h"
#include <cmath>

namespace potato_raycasting {

World::World(int imageScale, int colorScale,
             std::vector<std::vector<int>> worldMap)
    : _imageScale{imageScale}, _colorScale{colorScale}, _worldMap{worldMap},
      _player{10, 10, 0, 0xffffffff, 1.0} {}

void World::draw(Screen &screen) {
  for (int x{0}; x < _worldMap.size(); x++) {
    for (int y{0}; y < _worldMap.at(0).size(); y++) {
      for (int xs{x * _imageScale}; xs < (x + 1) * _imageScale; xs++) {
        for (int ys{y * _imageScale}; ys < (y + 1) * _imageScale; ys++) {
          screen.put(xs, ys, _worldMap[x][y] * _colorScale);
        }
      }
    }
  }

  int playerX{static_cast<int>(_player.pos.x)};
  int playerY{static_cast<int>(_player.pos.y)};

  for (int xs{playerX * _imageScale}; xs < (playerX + 1) * _imageScale; xs++) {
    for (int ys{playerY * _imageScale}; ys < (playerY + 1) * _imageScale;
         ys++) {
      screen.put(xs, ys, _player.color);
    }
  }

  screen.drawLineDDA(playerX * _imageScale, playerY * _imageScale,
                     playerX * _imageScale + 30 * _player.dir.x,
                     playerY * _imageScale + 30 * _player.dir.y,
                     0xff4400ff);
}

void World::controls(PlayerControls controls) { _player.move(controls); }
} // namespace potato_raycasting
