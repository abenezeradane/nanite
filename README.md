# Nanite
> A minimal SDL2 and OpenGL implementation

Nanite is the application implementation I use in nano, a custom game engine I wrote from scratch in C.

### Features
#### Currently Implemented
- [x] Window Creation
- [x] Basic Input Handling
- [ ] Simple Shader Rendering

#### Planned Features
- [ ] More Robust Input Handling

### Usage
Nanite is a single-header library, so just drop `nanite.h` into your project to get started/.
```c
/**
 * Simple Implementation
 */
#define INPUT_IMPLEMENTATION
#define RENDER_IMPLEMENTATION
#define APPLICATION_IMPLEMENTATION
#include "nanite.h"

static void load(void);
static void frame(void);

static Application app;
int WinMain(int argc, char const *argv[]) {
  app.load = load;
  app.step = frame;
  app.vsync = true;
  app.title = "Darkness";

  start(&app);
  return 0;
}

static void load(void) {
  
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    app.quit = true;

  if (keypress(KEY_F))
    fullscreen(&app);
}
```

### Dependencies
- [SDL2](https://www.libsdl.org/)
- [GLEW](http://glew.sourceforge.net/)
