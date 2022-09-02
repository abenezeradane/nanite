#define NANITE_IMPLEMENTATION
#include "nanite.h"

static void load(void);

/**
 * @brief Simple Implementation
 */
static Application app;
int WinMain(void) {
  // Specify the load function (which is ran on window creation)
  app.load = load;
  run(&app);
  return 0;
}

static void load(void) {
  // Create an entity and a shader
  createEntity("Entity", (int[2]) {4, 4}, (float[3]) {0.0f, 0.0f, 0.0f});
  createShader("Entity", "shaders/basic.vert", "shaders/basic.frag");
}