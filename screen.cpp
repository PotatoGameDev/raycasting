#include <cmath>
#include "screen.h" 

const unsigned width {800};
const unsigned height {600};

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void draw_point(std::vector<uint32_t>& buffer, int x, int y, uint32_t color) {
    buffer[x * width + y] = color;
}


void draw_line_dda(std::vector<uint32_t>& buffer, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx {x1 - x0};
    int dy {y1 - y0};

    int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

    float ix {dx / static_cast<float>(steps)};
    float iy {dy / static_cast<float>(steps)};
    
    float x {static_cast<float>(x0)};
    float y {static_cast<float>(y0)};
    
    for (int i {}; i <= steps; i++) {
	    draw_point(buffer, x, y, color);
	    x += ix;
	    y += iy;
    }
}


void draw_line_bresenham(std::vector<uint32_t>& buffer, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2;

    while(true) {
        draw_point(buffer, x0, y0, color);
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

constexpr float degrees_to_radians(int degrees) {
    return degrees * (M_PI / 180.0f);
}

void draw_radar(std::vector<uint32_t>& buffer, int cx, int cy, float angle, int radius, uint32_t color, bool dda) {    
    float angleRadians = degrees_to_radians(angle);
    int x = static_cast<int>(cx + radius * std::cos(angleRadians));
    int y = static_cast<int>(cy + radius * std::sin(angleRadians));
    
    if (dda) {
	    draw_line_dda(buffer, cx, cy, x, y, color);
    } else {
	    draw_line_bresenham(buffer, cx, cy, x, y, color);
    }
}


