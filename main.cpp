#include "MiniFB.h"
#include "MiniFB_enums.h"
#include <cmath>
#include <cstdint>
#include <vector>
#include <memory>
#include <utility>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


auto mfbDeleter = [](mfb_window* ptr) {
    if (ptr != nullptr) {
        mfb_close(ptr);
    }
};

int image_scale {20};
int color_scale {100};

std::vector<std::vector<int>> worldMap
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const unsigned width {800};
const unsigned height {600};

const float speed {0.1};

std::pair<float, float> player_pos{ 2.0, 2.0 };

std::vector<uint32_t> buffer(width * height);

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
        if (x0 == x1 && y0 == y1) break;
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


void draw_map(std::vector<uint32_t>& buffer, std::pair<float, float> player_pos) {
    for (unsigned x = 0; x < height; ++x) {
        for (unsigned y = 0; y < width; ++y) {
            draw_point(buffer, x, y, 0x11111100);

            if (x/image_scale < worldMap.size() && y/ image_scale < worldMap[0].size()) {
                uint32_t map_point = worldMap[x/image_scale][y/image_scale] * color_scale;
		draw_point(buffer, x, y, map_point);
            }
	    if (x/image_scale == static_cast<int>(player_pos.first) && y/image_scale == static_cast<int>(player_pos.second)) {
		draw_point(buffer, x, y, 0xffffffff);
	    }
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

void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) {
    // Remember to close the window in some way
    if(key == KB_KEY_ESCAPE) {
        mfb_close(window);
    } else if (key == KB_KEY_UP) {
	player_pos.first -= speed;	
    } else if (key == KB_KEY_DOWN) {
	player_pos.first += speed;	
    } else if (key == KB_KEY_LEFT) {
	player_pos.second -= speed;	
    } else if (key == KB_KEY_RIGHT) {
	player_pos.second += speed;	
    }
}


int main() {
    std::unique_ptr<struct mfb_window, decltype(mfbDeleter)> window(mfb_open("Frodo Lives", width, height), mfbDeleter);
    if (!window) {
        return -1;
    }

    int off {100};

    mfb_set_keyboard_callback(window.get(), keyboard);


    int angle {};

    while (mfb_wait_sync(window.get())) {
        if (mfb_update(window.get(), buffer.data()) < 0) {
            break;
        }
	draw_map(buffer, player_pos);

	draw_line_dda(buffer, 100, 100, 50, 70, 0xff0000ff);
	draw_line_dda(buffer, 100, 100, 120, 60, 0x00ff00ff);
	draw_line_dda(buffer, 100, 100, 50, 160, 0xffffffff);
	draw_line_dda(buffer, 100, 100, 156, 151, 0x0000ffff);

	
	draw_line_dda(buffer, 100, 100, 100, 70, 0xff0000ff);
	draw_line_dda(buffer, 100, 100, 100, 150, 0xff0000ff);
	draw_line_dda(buffer, 100, 100, 50, 100, 0xff0000ff);
	draw_line_dda(buffer, 100, 100, 190, 100, 0xff0000ff);

	draw_line_bresenham(buffer, 100 + off, 100 + off, 50 + off, 70 + off, 0xff0000ff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 120 + off, 60 + off, 0x00ff00ff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 50 + off, 160 + off, 0xffffffff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 156 + off, 151 + off, 0x0000ffff);

	
	draw_line_bresenham(buffer, 100 + off, 100 + off, 100 + off, 70 + off, 0xff0000ff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 100 + off, 150 + off, 0xff0000ff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 50 + off, 100 + off, 0xff0000ff);
	draw_line_bresenham(buffer, 100 + off, 100 + off, 190 + off, 100 + off, 0xff0000ff);

	draw_radar(buffer, 100, 100, angle, 20, 0xff2233ff, true);
	draw_radar(buffer, 200, 200, angle, 20, 0x4422ffff, false);

	angle++;
    }

    return 0;
}


