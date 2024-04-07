#include "world.h"

namespace potato_raycasting {

void World::drawPoint(int mapX, int mapY, uint32_t colour, Screen &screen) {
  for (int xs{mapX * _imageScale}; xs < (mapX + 1) * _imageScale; xs++) {
    for (int ys{mapY * _imageScale}; ys < (mapY + 1) * _imageScale; ys++) {
      screen.put(xs, ys, colour);
    }
  }
}

RayHit World::raycast(const Ray &ray) {
  float rayDirX = ray.dir.x;
  float rayDirY = ray.dir.y;
  float posX = ray.from.x;
  float posY = ray.from.y;

  int mapX = int(posX);
  int mapY = int(posY);

  double sideDistX;
  double sideDistY;

  double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
  double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
  double perpWallDist;

  int stepX;
  int stepY;

  int hit = 0;
  int side;

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

  while (hit == 0) {
    if (sideDistX < sideDistY) {
      sideDistX += deltaDistX;
      mapX += stepX;
      side = 0;
    } else {
      sideDistY += deltaDistY;
      mapY += stepY;
      side = 1;
    }

    if (_worldMap[mapX][mapY] > 0) {
      return {
          _worldMap[mapX][mapY], side,
          ray.from.dist({static_cast<float>(mapX), static_cast<float>(mapY)})};
    }
  }
  throw "Shit";
}

World::World(int imageScale, int colorScale,
             std::vector<std::vector<int>> worldMap)
    : _imageScale{imageScale}, _colorScale{colorScale}, _worldMap{worldMap},
      _player{10, 10, 0.0, 0xffffffff, 1.0}, _cam{0.0} {}

void World::draw(Screen &screen) {

  for (int x = 0; x < screen.dims().x; x++) {
    double cameraX =
        2 * x / double(screen.dims().x) - 1; // x-coordinate in camera space

    Ray ray = _cam.ray(_player.pos, _player.dir, cameraX);

    RayHit hit = raycast(ray);

    int lineHeight = (int)(screen.dims().y / hit.dist);

    int drawStart = -lineHeight / 2 + screen.dims().y / 2;
    if (drawStart < 0) {
      drawStart = 0;
    }
    int drawEnd = lineHeight / 2 + screen.dims().y / 2;
    if (drawEnd >= screen.dims().y) {
      drawEnd = screen.dims().y - 1;
    }

    Vector2 start{x, drawStart};
    Vector2 end{x, drawEnd};

    screen.drawLineDDA(start, end, hit.type * _colorScale);
  }

  // draw world map
  for (int x{0}; x < _worldMap.size(); x++) {
    for (int y{0}; y < _worldMap.at(0).size(); y++) {
      this->drawPoint(y, x, _worldMap[x][y] * _colorScale, screen);
    }
  }

  // draw camera view
  Vector2 camB = _cam.start(_player.pos, _player.dir) * _imageScale;
  Vector2 camE = _cam.end(_player.pos, _player.dir) * _imageScale;

  screen.drawLineDDA(camB.x, camB.y, camE.x, camE.y, 0xff4400ff);

  // draw player
  Ray example = _cam.ray(_player.pos, _player.dir, -1.0);
  screen.drawRay(example * _imageScale, 0xff0000ff);
  Ray example1 = _cam.ray(_player.pos, _player.dir, 0.0);
  screen.drawRay(example1 * _imageScale, 0x00ff00ff);
  Ray example2 = _cam.ray(_player.pos, _player.dir, 1.0);
  screen.drawRay(example2 * _imageScale, 0xff0000ff);
}

void World::controls(PlayerControls controls) {
  _player.move(controls);
  _cam.angle(_player.angle);
}
} // namespace potato_raycasting
