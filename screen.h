#ifndef POTATO_SCREEN_H
#define POTATO_SCREEN_H

#include <cstdint>
#include <vector>


void draw_point(std::vector<uint32_t>&, int, int, uint32_t);

void draw_line_dda(std::vector<uint32_t>&, int, int, int, int, uint32_t);

void draw_line_bresenham(std::vector<uint32_t>&, int, int, int, int, uint32_t);

constexpr float degrees_to_radians(int);

void draw_radar(std::vector<uint32_t>&, int, int, float, int, uint32_t, bool);

#endif // POTATO_SCREEN_H
