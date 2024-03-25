#include "player.h"
#include "screen.h"
#include "world.h"

using namespace potato_raycasting;

World world{10};

void keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod,
              bool isPressed) {
  if (key == KB_KEY_ESCAPE) {
    mfb_close(window);
  } else if (key == KB_KEY_UP) {
    world.controls(PlayerControls::up);
  } else if (key == KB_KEY_DOWN) {
    world.controls(PlayerControls::down);
  } else if (key == KB_KEY_LEFT) {
    world.controls(PlayerControls::left);
  } else if (key == KB_KEY_RIGHT) {
    world.controls(PlayerControls::right);
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
