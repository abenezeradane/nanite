## nanite
> A minimal, single-header, SDL2 and OpenGL implementation

**nanite** is an SDL2 and OpenGL application implementation I use whenever I am working with SDL2.

### Features
#### Currently Implemented
- [x] Window Creation
- [x] Basic Input Handling

#### Planned Features
- [ ] Simple Shader Rendering
- [ ] Simple Texture Rendering
- [ ] Robust Input Handling w/ Input Mapping
- [ ] Robust Texture Rendering
- [ ] Robust Shader Rendering
- [ ] GLFW and Vulkan Support

### Usage
Nanite is a single-header library, so just drop `nanite.h` into your project to get started/.
```c
/**
 * Simple Implementation
 */
#define FULL_NANITE_IMPLEMENTATION
#include "nanite.h"

static void load(void);
static void frame(void);

static Application app;
int WinMain(int argc, char const *argv[]) {
  app.load = load;
  app.step = frame;

  start(&app);
  return 0;
}

static void load(void) {
  
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    app.quit = true;
}
```

### Dependencies
- [SDL2](https://www.libsdl.org/)
- [GLEW](http://glew.sourceforge.net/)
