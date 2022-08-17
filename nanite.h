#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Prints a formatted string to the console.
 * @param msg Error message.
 */
void error(char* msg) {
  fprintf(stderr, "\x1b[5m\x1B[31mError\x1B[0m: %s\n", msg);
  exit(EXIT_FAILURE);
}

#endif      // MISCELLANEOUS_H

#ifndef INPUT_INCLUDE
#define INPUT_INCLUDE

/**
 * @brief Application input key enumeration.
 */
typedef enum KEY {
  KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
  KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
  KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
  KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

  KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
  KEY_7, KEY_8, KEY_9,

  KEY_ESCAPE, KEY_RETURN, KEY_LCTRL, KEY_LALT,
  KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
  KEY_LSHIFT, KEY_SPACE,

  KEY_MAX
} KEY;

/**
 * @brief Application input key state enumeration.
 */
typedef enum KEYSTATE {
  KEY_STATE_RELEASED,
  KEY_STATE_PRESSED,
  KEY_STATE_HELD,
} KEYSTATE;

// TODO: Add support for mouse buttons.
// TODO: Add support for mouse wheel.

static KEYSTATE keybinds[KEY_MAX];

// Check if a key is pressed.
static bool keypress(KEY key);

// Update key states
static void update(uint8_t key, KEYSTATE* state);

// Input handler
static void input(void);

#endif    // INPUT_INCLUDE

#ifdef INPUT_IMPLEMENTATION
#undef INPUT_IMPLEMENTATION

/**
 * @brief Check if a key is pressed.
 * @param key SDL key
 */
bool keypress(KEY key) {
  return keybinds[key] > KEY_STATE_RELEASED;
}

/**
 * @brief Update key states.
 * @param key SDL key
 */
void update(uint8_t keyboard, KEYSTATE* state) {
  if (keyboard) {
    if (*state > KEY_STATE_RELEASED)
      *state = KEY_STATE_HELD;
    else
      *state = KEY_STATE_PRESSED;
  } else
    *state = KEY_STATE_RELEASED;
}

/**
 * @brief Input handler
 */
void input(void) {
  const uint8_t* state = SDL_GetKeyboardState(NULL);

  register KEY key;
  for (key = KEY_A; key < KEY_MAX; key++) {
    if (key >= KEY_A && key <= KEY_Z)
      update(state[SDL_SCANCODE_A + key], &keybinds[key]);
    else if (key >= KEY_0 && key <= KEY_9)
      update(state[SDL_SCANCODE_0 + key - KEY_0], &keybinds[key]);
    else {
      switch (key) {
        case KEY_ESCAPE: update(state[SDL_SCANCODE_ESCAPE], &keybinds[key]); break;
        case KEY_RETURN: update(state[SDL_SCANCODE_RETURN], &keybinds[key]); break;
        case KEY_LCTRL: update(state[SDL_SCANCODE_LCTRL], &keybinds[key]); break;
        case KEY_LALT: update(state[SDL_SCANCODE_LALT], &keybinds[key]); break;
        case KEY_LEFT: update(state[SDL_SCANCODE_LEFT], &keybinds[key]); break;
        case KEY_RIGHT: update(state[SDL_SCANCODE_RIGHT], &keybinds[key]); break;
        case KEY_UP: update(state[SDL_SCANCODE_UP], &keybinds[key]); break;
        case KEY_DOWN: update(state[SDL_SCANCODE_DOWN], &keybinds[key]); break;
        case KEY_LSHIFT: update(state[SDL_SCANCODE_LSHIFT], &keybinds[key]); break;
        case KEY_SPACE: update(state[SDL_SCANCODE_SPACE], &keybinds[key]); break;
        default: break;
      }
    }
  }
}

#endif    // INPUT_IMPLEMENTATION

#ifndef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE

/**
 * @brief Application struct.
 */
typedef struct Application {
  const char* title;
  SDL_Window* window;
  SDL_GLContext context;

  int x, y, width, height, fps;
  bool quit, vsync, cursor, fullscreen;

  void (*step)(void);
  void (*load)(void);
} Application;

// Time variables.
static float now;
static float last;
static float delta;

// Get the current time.
double time(void);

// Update fullscreen.
void fullcreen(Application* app);

// Update cursor.
void cursor(Application* app);

// Initializes the application.
void start(Application* app);

// Close the application.
void close(Application* app);

#endif    // APPLICATION_INCLUDE

#ifdef APPLICATION_IMPLEMENTATION
#undef APPLICATION_IMPLEMENTATION

/**
 * @brief Get time
 * 
 * @return double Get time in milliseconds
 */
double time(void) {
  return (double) SDL_GetTicks();
}

/**
 * @brief Update fullscreen.
 * @param app Application.
 */
void fullscreen(Application* app) {
  app -> fullscreen = !(app -> fullscreen);
  SDL_SetWindowFullscreen(app -> window, app -> fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

/**
 * @brief Update cursor.
 * @param app Application.
 */
void cursor(Application* app) {
  app -> cursor = !(app -> cursor);
  SDL_ShowCursor(app -> cursor);
}

/**
 * @brief Initializes the application.
 * @param app The application to initialize.
 */
void start(Application* app) {
  // Verify that the application isn't null.
  if (!app)
    error("Application is null!");

  // Initialize the SDL library.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0)
    error(strcat("SDL2 Failed to Initialize!\n> ", SDL_GetError()));

  // Set OpenGL attributes.
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create the window.
  app -> window = SDL_CreateWindow(
    app -> title ? app -> title : "Application",
    app -> x ? app -> x : SDL_WINDOWPOS_CENTERED,
    app -> y ? app -> y : SDL_WINDOWPOS_CENTERED,
    app -> width ? app -> width : 720,
    app -> height ? app -> height : 480,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  if ((app -> window) == NULL)
    error(strcat("SDL2 Failed to Create Window!\n> ", SDL_GetError()));

  // Create the OpenGL context.
  app -> context = SDL_GL_CreateContext(app -> window);
  if (!app -> context)
    error(strcat("SDL2 Failed to Create OpenGL Context!\n> ", SDL_GetError()));

  // Initialize GLEW.
  glewInit();
  SDL_GL_SetSwapInterval(app -> vsync);
  SDL_ShowCursor(app -> cursor);

  if (app -> load)
    app -> load();

  last = time();
  while (!(app -> quit)) {
    now = time();
    delta = now - last;

    if (delta > (1000 / (app -> fps ? app -> fps : 60))) {
      last = now;

      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          app -> quit = true;
      }

      input();
      if (app -> step)
        app -> step();
    }
  }
}

/**
 * @brief Close the application.
 * @param app The application to close.
 */
void close(Application* app) {
  // Verify that the application isn't null.
  if (!app)
    error("Application is null!");
  
  // Destroy the window.
  SDL_DestroyWindow(app -> window);
  SDL_Quit();
}

#endif    // APPLICATION_IMPLEMENTATION