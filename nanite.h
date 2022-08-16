#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

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

#ifndef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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