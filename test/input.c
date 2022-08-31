#define NANITE_IMPLEMENTATION
#include "nanite.h"

static void frame(void);

/**
 * @brief Simple Implementation
 */
static Application app;
int WinMain(void) {
  // Specify the step function (which is ran every frame)
  app.step = frame;
  run(&app);
  return 0;
}

static void frame(void) {
  // Exit if 'ESCAPE' is pressed
  if (keypress(KEY_ESCAPE))
    app.running = false;
}