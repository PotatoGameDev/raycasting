#include "world.h"

namespace potato_raycasting {

World::World(int imageScale, int colorScale,
             std::vector<std::vector<int>> worldMap)
    : _imageScale{imageScale}, _colorScale{colorScale}, _worldMap{worldMap},
      _player{10, 10, 0.0, 0xffffffff, 1.0}, _cam{0.0} {}

void World::draw(Screen &screen) {
  // draw world
  for (int x{0}; x < _worldMap.size(); x++) {
    for (int y{0}; y < _worldMap.at(0).size(); y++) {
      for (int xs{x * _imageScale}; xs < (x + 1) * _imageScale; xs++) {
        for (int ys{y * _imageScale}; ys < (y + 1) * _imageScale; ys++) {
          screen.put(xs, ys, _worldMap[x][y] * _colorScale);
        }
      }
    }
  }

  // draw the player
  /*
  int playerX{static_cast<int>(_player.pos.x)};
  int playerY{static_cast<int>(_player.pos.y)};

  for (int xs{playerX * _imageScale}; xs < (playerX + 1) * _imageScale; xs++) {
    for (int ys{playerY * _imageScale}; ys < (playerY + 1) * _imageScale;
         ys++) {
      screen.put(xs, ys, _player.color);
    }
  }
  */

  // draw players direction:
  screen.drawLineDDA(_player.pos * _imageScale,
                     _player.pos * _imageScale + 30 * _player.dir,
                     0x0f44000f);

  // draw camera view
  Vector2 camB = _cam.start(_player.pos, _player.dir) * _imageScale;
  Vector2 camE = _cam.end(_player.pos, _player.dir) * _imageScale;

  screen.drawLineDDA(camB.x, camB.y, camE.x, camE.y, 0xff4400ff);
  
  // draw example ray
  Ray example = _cam.ray(_player.pos, _player.dir, 0.0);
  screen.drawRay(example * _imageScale, 0xff0000ff);
  Ray example1 = _cam.ray(_player.pos, _player.dir, 0.666666);
  screen.drawRay(example1 * _imageScale, 0x00ff00ff);
  Ray example2 = _cam.ray(_player.pos, _player.dir, 1.0);
  screen.drawRay(example2 * _imageScale, 0xff0000ff);
}

void World::controls(PlayerControls controls) {
  _player.move(controls);
  _cam.angle(_player.angle);
}
} // namespace potato_raycasting
