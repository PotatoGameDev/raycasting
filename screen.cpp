#include "screen.h"
#include <cmath>

namespace potato_raycasting {

void Screen::drawPoint(int x, int y, uint32_t colour) {
  if (x > 0 && x < _height && y > 0 && y < _width) {
    _buffer[x * _width + y] = colour;
  }
}

void Screen::drawLineDDA(int x0, int y0, int x1, int y1, uint32_t colour) {
  int dx{x1 - x0};
  int dy{y1 - y0};

  int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  float ix{dx / static_cast<float>(steps)};
  float iy{dy / static_cast<float>(steps)};

  float x{static_cast<float>(x0)};
  float y{static_cast<float>(y0)};

  for (int i{}; i <= steps; i++) {
    drawPoint(x, y, colour);
    x += ix;
    y += iy;
  }
}

void Screen::drawLineDDA(const Vector2 &from, const Vector2 &to,
                         uint32_t colour) {
  drawLineDDA(from.x, from.y, to.x, to.y, colour);
}

void Screen::drawLineBresenham(int x0, int y0, int x1, int y1,
                               uint32_t colour) {
  int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  while (true) {
    drawPoint(x0, y0, colour);
    if (x0 == x1 && y0 == y1) {
      break;
    }
    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void Screen::drawRay(const Ray &ray, uint32_t colour) {
  drawLineDDA(ray.from, ray.through, colour);
}

constexpr float degrees_to_radians(int degrees) {
  return degrees * (M_PI / 180.0f);
}

void Screen::drawRadar(int cx, int cy, float angle, int radius, uint32_t colour,
                       bool dda) {
  float angleRadians = degrees_to_radians(angle);
  int x = static_cast<int>(cx + radius * std::cos(angleRadians));
  int y = static_cast<int>(cy + radius * std::sin(angleRadians));

  if (dda) {
    drawLineDDA(cx, cy, x, y, colour);
  } else {
    drawLineBresenham(cx, cy, x, y, colour);
  }
}

Screen::Screen(unsigned width, unsigned height)
    : _width{width}, _height{height}, _buffer(_width * _height) {
  _window = mfb_open("Frodo Lives", width, height);
  if (!_window) {
    throw "Could not initialize MiniFB window";
  }
}

void Screen::registerControls(mfb_keyboard_func controls) {
  mfb_set_keyboard_callback(_window, controls);
}

bool Screen::refresh() { return mfb_update(_window, _buffer.data()) < 0; }

void Screen::put(unsigned x, unsigned y, uint32_t colour) {
  drawPoint(x, y, colour);
}

bool Screen::sync() { return mfb_wait_sync(_window); }

Vector2 Screen::dims() {
  return {static_cast<float>(_width), static_cast<float>(_height)};
}

Screen::~Screen() {
  if (_window) {
    mfb_close(_window);
  }
}

} // namespace potato_raycasting
