#include "MiniFB.h"
#include "MiniFB_enums.h"
#include <vector>
#include <memory>
#include <utility>

auto mfbDeleter = [](mfb_window* ptr) {
    if (ptr != nullptr) {
        mfb_close(ptr);
    }
};

int image_scale = 20;
int color_scale = 100;

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

const unsigned width = 800;
const unsigned height = 600;

const float speed = 0.1;

std::pair<float, float> player_pos{ 2.0, 2.0 };

std::vector<uint32_t> buffer(width * height);
std::vector<std::vector<uint32_t>> buffer_internal(width, std::vector<uint32_t>(height, 0x11111100));




void draw_map(const std::vector<std::vector<uint32_t>>& buffer_internal, std::vector<uint32_t>& buffer, std::pair<float, float> player_pos) {
    for (unsigned x = 0; x < height; ++x) {
        for (unsigned y = 0; y < width; ++y) {
            buffer[x * width + y] = buffer_internal[y][x];

            if (x/image_scale < worldMap.size() && y/ image_scale < worldMap[0].size()) {
                buffer[x * width + y] = worldMap[x/image_scale][y/image_scale] * color_scale;
            }
	    if (x/image_scale == static_cast<int>(player_pos.first) && y/image_scale == static_cast<int>(player_pos.second)) {
		buffer[x * width + y] = 0xffffffff;
	    }
        }
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

    mfb_set_keyboard_callback(window.get(), keyboard);

    while (mfb_wait_sync(window.get())) {
        if (mfb_update(window.get(), buffer.data()) < 0) {
            break;
        }
	draw_map(buffer_internal, buffer, player_pos);
    }

    return 0;
}


