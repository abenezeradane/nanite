#define NANITE_IMPLEMENTATION
#include "nanite.h"

/**
 * @brief Simple Implementation
 */
int WinMain(void) {
  // Specify window attributes
  Application app = {
    .title = "Hello World",
    .width = 640,
    .height = 480,

    .vsync = true,
    .fullscreen = false,
  };

  run(&app);
  return 0;
}