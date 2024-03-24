#ifndef POTATO_SCREEN_H
#define POTATO_SCREEN_H

#include "MiniFB.h"
#include "MiniFB_enums.h"
#include <cstdint>
#include <vector>

namespace potato_raycasting {
void draw_line_dda(std::vector<uint32_t> &, int, int, int, int, uint32_t);

void draw_line_bresenham(std::vector<uint32_t> &, int, int, int, int, uint32_t);

constexpr float degrees_to_radians(int);

void draw_radar(std::vector<uint32_t> &, int, int, float, int, uint32_t, bool);

class Screen {
private:
  unsigned _width;
  unsigned _height;

  std::vector<uint32_t> _buffer;

  struct mfb_window *_window;

  void drawPoint(int, int, uint32_t);
  void drawLineDDA(int, int, int, int, uint32_t);
  void drawLineBresenham(int, int, int, int, uint32_t);
  void drawRadar(int, int, float, int, uint32_t, bool);

public:
  Screen(unsigned, unsigned);
  ~Screen();

  void registerControls(mfb_keyboard_func);

  bool refresh();
  void put(unsigned, unsigned, uint32_t);

  bool sync();
};

} // namespace potato_raycasting

#endif // POTATO_SCREEN_H
