## nanite
> A minimal, single-header, implementation for window creation, input handling and graphics rendering

**nanite** is an SDL2 and OpenGL application implementation I use whenever I am working with SDL2.

### Features
#### Currently Implemented
- [x] Window Creation
- [x] Basic Input Handling

#### Planned Features
- [ ] Simple Shader Rendering
- [ ] Simple Texture Rendering
- [ ] Window Management (Resize, Maximize, Minimize, etc)
- [ ] Robust Input Handling w/ Input Mapping
- [ ] Robust Texture Rendering
- [ ] Robust Shader Rendering
- [ ] GLFW and SFML Support
- [ ] Vulkan, Metal, and D3D12 Support

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
int WinMain(int argc, const char *argv[]) {
  app.load = load;
  app.step = frame;

  start(&app);
  return 0;
}

static void load(void) {
  
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    app.running = true;
}
```

### Dependencies
- [SDL2](https://www.libsdl.org/)
- [GLEW](http://glew.sourceforge.net/)
