#include "world.h"
#include <iostream>

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
                     _player.pos * _imageScale + 30 * _player.dir, 0x0f44000f);

  // draw camera view
  Vector2 camB = _cam.start(_player.pos, _player.dir) * _imageScale;
  Vector2 camE = _cam.end(_player.pos, _player.dir) * _imageScale;

  screen.drawLineDDA(camB.x, camB.y, camE.x, camE.y, 0xff4400ff);

  // draw example ray
  Ray example = _cam.ray(_player.pos, _player.dir, -1.0);
  screen.drawRay(example * _imageScale, 0xff0000ff);
  Ray example1 = _cam.ray(_player.pos, _player.dir, 0.0);
  screen.drawRay(example1 * _imageScale, 0x00ff00ff);
  Ray example2 = _cam.ray(_player.pos, _player.dir, 1.0);
  screen.drawRay(example2 * _imageScale, 0xff0000ff);

  float rayDirX = example.dir.x;
  float rayDirY = example.dir.y;
  float posX = example.from.x;
  float posY = example.from.y;

  std::cout << rayDirX << " " << rayDirY << " - " << posX << " " << posY << std::endl;

  // which box of the map we're in
  int mapX = int(posX);
  int mapY = int(posY);

  // length of ray from current position to next x or y-side
  double sideDistX;
  double sideDistY;

  // length of ray from one x or y-side to next x or y-side
  double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
  double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
  double perpWallDist;

  // what direction to step in x or y-direction (either +1 or -1)
  int stepX;
  int stepY;

  int hit = 0; // was there a wall hit?
  int side;    // was a NS or a EW wall hit?

  // calculate step and initial sideDist
  if (rayDirX < 0) {
    stepX = -1;
    sideDistX = (posX - mapX) * deltaDistX;
  } else {
    stepX = 1;
    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
  }
  if (rayDirY < 0) {
    stepY = -1;
    sideDistY = (posY - mapY) * deltaDistY;
  } else {
    stepY = 1;
    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
  }

  // perform DDA
  while (hit == 0) {
    // jump to next map square, either in x-direction, or in y-direction
    if (sideDistX < sideDistY) {
      sideDistX += deltaDistX;
      mapX += stepX;
      side = 0;
    } else {
      sideDistY += deltaDistY;
      mapY += stepY;
      side = 1;
    }

    for (int xs{mapX * _imageScale}; xs < (mapX + 1) * _imageScale; xs++) {
      for (int ys{mapY * _imageScale}; ys < (mapY + 1) * _imageScale; ys++) {
        screen.put(xs, ys, 0x0000ff00);
      }
    }
    // Check if ray has hit a wall
    if (_worldMap[mapX][mapY] > 0)
      hit = 1;
  }
  
  screen.drawRay(example * _imageScale, 0xff0000ff);
}

void World::controls(PlayerControls controls) {
  _player.move(controls);
  _cam.angle(_player.angle);
}
} // namespace potato_raycasting
