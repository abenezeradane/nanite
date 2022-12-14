## nanite
> A minimal, single-header, implementation for window creation, input handling and graphics rendering

**Nanite** is a minimal all-in-one library for creating and rendering windows in a cross-platform manner, specifically for use in **nano**, a minimal cross-platform game engine written in **C**. Nanite is designed to be used as a single-header library, and is not intended to be used as a standalone application. Specifically, it does not include any user interface or mathematical functionality. It is intended to be used as a base for other libraries and is recommended that specific use cases be designed and implemented separately (e.g. a custom rendering pipeline, a custom input handling/mapping, etc.).

### Features
#### Window Creation
* Create a window with a title and dimensions
* Specify window attributes (e.g. fullscreen, vsync, etc)
* Specify the step function (which is ran every frame)
* Specify the load function (which is window creation)
* Update window attributes (e.g. title, dimensions, vsync, etc)
* Close the application

```c
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
```

#### Basic Input Handling
* Handle keyboard input
* Handle window close events

```c
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

  // Toggle fullscreen if 'F' is pressed
  if (keypress(KEY_F))
    setFullscreen(&app);
}
```

#### Rendering
* Render a simple shader

```c
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
```

### Planned Features
#### Input Handling
* Handle multiple input sources (e.g. mouse, gamepad, etc)
* Implement input mapping (e.g. keyboard mapping, gamepad mapping, etc)

#### Rendering
* Render a texture
* Render a shader with multiple textures

#### Window Creation Library
* [GLFW](https://www.glfw.org/)
* [SFML](http://www.sfml-dev.org/)

#### Graphics Library
* [Vulkan](https://www.khronos.org/vulkan/index.html)
* [Metal](https://developer.apple.com/metal/Metal.html)
* [Direct3D](https://www.microsoft.com/en-us/download/details.aspx?id=55653)

### Current Dependencies
* [SDL2](https://www.libsdl.org/release/)
* [GLEW](https://glew.sourceforge.net/basic.html)