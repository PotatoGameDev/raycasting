#include "player.h"
#include "screen.h"
#include "world.h"
#include <iostream>

using namespace potato_raycasting;

World world{};

void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod,
              bool isPressed) {
  if (key == KB_KEY_ESCAPE) {
    mfb_close(window);
  } else if (key == KB_KEY_UP) {
    world.controls(PlayerControls::north);
  } else if (key == KB_KEY_DOWN) {
    world.controls(PlayerControls::south);
  } else if (key == KB_KEY_LEFT) {
    world.controls(PlayerControls::west);
  } else if (key == KB_KEY_RIGHT) {
    world.controls(PlayerControls::east);
  }
}

int main() {
  Screen screen(800, 600);
  screen.registerControls(keyboard);

  while (screen.sync()) {
    if (screen.refresh()) {
      break;
    }
    world.draw(screen);
  }

  return 0;
}
