#include "world.h"
#include "util.h"
#include <cmath>

namespace potato_raycasting {

World::World(int imageScale, std::vector<std::vector<int>> worldMap)
    : _imageScale{imageScale}, _worldMap(transpose(worldMap)),
      _player{10, 20, 0.0, 0xffffffff, 1.0}, _cam{0.0, 1.0} {}

void World::drawPoint(int mapX, int mapY, uint32_t colour, Screen &screen) {
    for (int xs{mapX * _imageScale}; xs < (mapX + 1) * _imageScale; xs++) {
        for (int ys{mapY * _imageScale}; ys < (mapY + 1) * _imageScale; ys++) {
            screen.put(xs, ys, colour);
        }
    }
}

uint32_t wallTypeToColour(int wallType) {
    uint32_t colour;
    switch (wallType) {
    case 1:
        colour = 0xFFFF0000;
        break;
    case 2:
        colour = 0xFF00FF00;
        break;
    case 3:
        colour = 0xFF0000FF;
        break;
    case 4:
        colour = 0xFFFFFFFF;
        break;
    case 5:
        colour = 0xFFFFFFFF;
        break;
    case 6:
        colour = 0xFFFFFFFF;
        break;
    default:
        colour = 0xFF000000;
        break;
    }

    return colour;
}

uint32_t applyDistanceFactorToColor(uint32_t color, float factor) {
    uint8_t alpha = (color >> 24) & 0xFF;
    uint8_t red = (color >> 16) & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t blue = color & 0xFF;

    alpha = static_cast<uint8_t>(
        std::max(0, std::min(255, static_cast<int>(alpha * factor))));
    red = static_cast<uint8_t>(
        std::max(0, std::min(255, static_cast<int>(red * factor))));
    green = static_cast<uint8_t>(
        std::max(0, std::min(255, static_cast<int>(green * factor))));
    blue = static_cast<uint8_t>(
        std::max(0, std::min(255, static_cast<int>(blue * factor))));

    return (static_cast<uint32_t>(alpha) << 24) |
           (static_cast<uint32_t>(red) << 16) |
           (static_cast<uint32_t>(green) << 8) | static_cast<uint32_t>(blue);
}

RayHit World::raycast(const Ray &ray) {
    float rayDirX = ray.dir.x;
    float rayDirY = ray.dir.y;
    float posX = ray.from.x;
    float posY = ray.from.y;

    int mapX = int(posX);
    int mapY = int(posY);

    float sideDistX;
    float sideDistY;

    float deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1.0 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1.0 / rayDirY);
    float perpWallDist;

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
            if (side == 0) {
                perpWallDist = (sideDistX - deltaDistX);
            } else {
                perpWallDist = (sideDistY - deltaDistY);
            }

            return {_worldMap[mapX][mapY], side, perpWallDist};
        }
    }
    throw "All problem all bad";
}

void World::draw(Screen &screen) {
    // draw floor and ceiling
    for (int y = 0; y < screen.dims().y; y++) {
        float ratio;
        if (y < screen.dims().y / 2) {
            ratio = static_cast<float>(y) / (screen.dims().y / 2);
            uint32_t colour =
                applyDistanceFactorToColor(0xFF222222, 1.0f - ratio);
            screen.drawLineDDA(0, y, screen.dims().x, y, colour);
        } else {
            ratio =
                static_cast<float>(screen.dims().y - y) / (screen.dims().y / 2);
            uint32_t colour =
                applyDistanceFactorToColor(0xFF444444, 1.0f - ratio);
            screen.drawLineDDA(0, y, screen.dims().x, y, colour);
        }
    }

    // draw world
    for (int x = 0; x < screen.dims().x; x++) {
        double cameraX = 2 * x / double(screen.dims().x) - 1;

        Ray ray = _cam.ray(_player.pos, _player.dir, cameraX);

        RayHit hit = raycast(ray);

        // Fisheye correction:
        Vector2 playerDir = _player.dir.normalized();
        Vector2 rayDir = ray.dir.normalized();

        float cosTheta = playerDir.dot(rayDir);
        float correctedDistance = hit.dist * cosTheta;

        int lineHeight = static_cast<int>(screen.dims().y / correctedDistance);
        int drawStart = -static_cast<int>(lineHeight / 2) + screen.dims().y / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = static_cast<int>(lineHeight / 2) + screen.dims().y / 2;
        if (drawEnd >= screen.dims().y) {
            drawEnd = screen.dims().y - 1;
        }

        Vector2 start{x, drawStart};
        Vector2 end{x, drawEnd};

        uint32_t colour = wallTypeToColour(hit.type);

        if (hit.side == 0) {
            colour = applyDistanceFactorToColor(colour, 0.5f);
        }

        float distance = hit.dist;
        float maxDistance = 12.0f;
        float distanceFactor = 1.0f - (distance / maxDistance);

        colour = applyDistanceFactorToColor(colour, distanceFactor);

        screen.drawLineDDA(start, end, colour);
    }

    // draw world map
    for (int x{0}; x < _worldMap.size(); x++) {
        for (int y{0}; y < _worldMap.at(0).size(); y++) {
            uint32_t colour = wallTypeToColour(_worldMap[x][y]);

            float distance = _player.pos.dist(Vector2(x, y));
            float maxDistance = 12.0f;
            float distanceFactor = 1.0f - (distance / maxDistance);
            colour = applyDistanceFactorToColor(colour, distanceFactor);
            this->drawPoint(x, y, colour, screen);
        }
    }

    // draw camera view
    Vector2 playerPos{_player.pos};
    Vector2 camB = _cam.start(playerPos, _player.dir) * _imageScale;
    Vector2 camE = _cam.end(playerPos, _player.dir) * _imageScale;

    screen.drawLineDDA(camB.x, camB.y, camE.x, camE.y, 0xFF4400FF);

    // draw player
    Ray example = _cam.ray(playerPos, _player.dir, -1.0);
    screen.drawRay(example * _imageScale, 0xFF0000FF);
    Ray example1 = _cam.ray(playerPos, _player.dir, 0.0);
    screen.drawRay(example1 * _imageScale, 0x00FF00FF);
    Ray example2 = _cam.ray(playerPos, _player.dir, 1.0);
    screen.drawRay(example2 * _imageScale, 0xFF0000FF);
}

void World::controls(PlayerControls controls) {
    Vector2 intent = _player.newPos(controls);
    if (intent.x > 0 && intent.x < _worldMap.size() && intent.y > 0 &&
        intent.y < _worldMap.at(0).size() &&
        _worldMap[static_cast<int>(intent.x)]
                 [static_cast<int>(intent.y)] == 0) {
        _player.move(controls);
        _cam.angle(_player.angle);
    }
}
} // namespace potato_raycasting
