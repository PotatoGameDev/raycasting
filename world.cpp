#include "world.h"

namespace potato_raycasting {

World::World(std::vector<std::vector<int>> worldMap, int imageScale,
             int colorScale)
    : _imageScale{imageScale}, _colorScale{colorScale}, _worldMap{worldMap},
      _player{10, 10, 0xffffffff, 1.0} {}

void World::draw(Screen &screen) {
  for (int x{0}; x < _worldMap.at(0).size(); x++) {
    for (int y{0}; y < _worldMap.size(); y++) {
      for (int xs{x * _imageScale}; xs < (x + 1) * _imageScale; xs++) {
        for (int ys{y * _imageScale}; ys < (y + 1) * _imageScale; ys++) {
          screen.put(xs, ys, _worldMap[x][y] * _colorScale);
        }
      }
    }
  }

  //std::cout << _player.x << " " << _player.y << std::endl;
  int playerX {static_cast<int>(_player.x)};
  int playerY {static_cast<int>(_player.y)};

  for (int xs{playerY * _imageScale}; xs < (playerY + 1) * _imageScale;
       xs++) {
    for (int ys{playerX * _imageScale}; ys < (playerX + 1) * _imageScale;
         ys++) {
      screen.put(xs, ys, _player.color);
    }
  }
}

void World::controls(PlayerControls controls) { _player.move(controls); }
} // namespace potato_raycasting
