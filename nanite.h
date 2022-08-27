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
 * @brief Prints an error message and exits the program.
 * 
 * @param msg The error message to print.
 */
void error(char* msg) {
  fprintf(stderr, "\x1b[5m\x1B[31mError\x1B[0m: %s\n", msg);
  exit(EXIT_FAILURE);
}

#endif // MISCELLANEOUS_H

#ifdef NANITE_IMPLEMENTATION
  #ifndef NANITE_INPUT_IMPLEMENTATION
  #define NANITE_INPUT_IMPLEMENTATION
  #endif

  #ifndef NANITE_APPLICATION_IMPLEMENTATION
  #define NANITE_APPLICATION_IMPLEMENTATION
  #endif
#endif // NANITE_IMPLEMENTATION

#ifndef NANITE_APPLICATION_INCLUDE
#define NANITE_APPLICATION_INCLUDE

/**
 * @brief The application structure.
 */
typedef struct Application {
  char* title;            // The title of the application.
  SDL_Window* window;     // The SDL window.
  SDL_GLContext context;  // The SDL OpenGL context.

  int x, y;               // The x and y position of the window.
  int width, height;      // The width and height of the window.
  int fps;                // The frames per second.

  bool running;           // Whether the application is running.
  bool fullscreen, vsync; // Whether the window is fullscreen and vsync is enabled.
  
  void (*load)(void);     // The function to call when the application is loaded.
  void (*step)(void);     // The function to call when the application is stepped.
} Application;

// Time variables.
static float now;
static float last;
static float delta;

/**
 * @brief Gets the time in milliseconds since the application started.
 */
static double time(void);

/**
 * @brief Initializes the application.
 * 
 * @param app The application to initialize.
 */
void run(Application* app);

/**
 * @brief Frees the application.
 * 
 * @param app The application to free.
 */
void close(Application* app);

#endif // NANITE_APPLICATION_INCLUDE

#ifdef NANITE_APPLICATION_IMPLEMENTATION
#undef NANITE_APPLICATION_IMPLEMENTATION

/**
 * @brief Gets the time in milliseconds since the application started.
 */
static double time(void) {
  return (double) SDL_GetTicks();
}

/**
 * @brief Initializes the application.
 * 
 * @param app The application to initialize.
 */
void run(Application* app) {
  // Check if the application is null.
  if (!app)
    error("Application is null.");

  // Set application properties.
  if (!(app -> title))
    app -> title = "nanite";
  if (!(app -> x))
    app -> x = SDL_WINDOWPOS_CENTERED;
  if (!(app -> y))
    app -> y = SDL_WINDOWPOS_CENTERED;
  if (!(app -> width))
    app -> width = 640;
  if (!(app -> height))
    app -> height = 480;
  if (!(app -> fps))
    app -> fps = 60;
  if (!(app -> fullscreen))
    app -> fullscreen = false;
  if (!(app -> vsync))
    app -> vsync = true;

  printf("\x1b[5m\x1B[32mInitializing\x1B[0m: \"%s\"\n", app -> title);

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0)
    error(strcat("SDL2 Failed to Initialize!\n> ", SDL_GetError()));

  // Set OpenGL attributes.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

  // Initialize the window.
  app -> window = SDL_CreateWindow(
    app -> title,
    app -> x, app -> y,
    app -> width, app -> height,
    SDL_WINDOW_OPENGL | (app -> fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
  );

  // Check if the window failed to initialize.
  if (!app -> window)
    error(strcat("SDL2 Failed to Create Window!\n> ", SDL_GetError()));

  // Initialize the OpenGL context.
  app -> context = SDL_GL_CreateContext(app -> window);
  if (!app -> context)
    error(strcat("SDL2 Failed to Create OpenGL Context!\n> ", SDL_GetError()));

  // Initialize GLEW.
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    error(strcat("GLEW Failed to Initialize!\n> ", glewGetErrorString(glewInit())));

  // Set the vsync.
  if (app -> vsync)
    SDL_GL_SetSwapInterval(1);
  else
    SDL_GL_SetSwapInterval(0);

  // Call the load function.
  if (app -> load)
    app -> load();

  printf("\x1b[1A\x1b[0K\x1b[5m\x1B[32mInitialized\x1B[0m: \"%s\"\n", app -> title);

  printf("\x1b[5m\x1B[32mRunning\x1B[0m: \"%s\"\n", app -> title);

  // Main loop.
  last = time();
  app -> running = true;
  while (app -> running) {

    // Get the time.
    now = time();
    delta = now - last;

    // Wait for the next frame.
    if (delta > (1000.0 / app -> fps)) {
      // Poll for events.
      SDL_Event event;
      if (SDL_PollEvent(&event)) {
        // Check for quit.
        if (event.type == SDL_QUIT)
          app -> running = false;
      }

      // Call the step function.
      if (app -> step)
        app -> step();

      // Swap the buffers.
      SDL_GL_SwapWindow(app -> window);

      // Update the last time.
      last = now;
    }
    else
      SDL_Delay((1000.0 / app -> fps) - delta);
  }

  close(app);
}

/**
 * @brief Frees the application.
 * 
 * @param app The application to free.
 */
void close(Application* app) {
  // Check if the application is null.
  if (!app)
    error("Application is null.");

  printf("\x1b[5m\x1B[32mClosing\x1B[0m: \"%s\"\n", app -> title);

  // Free the window.
  SDL_DestroyWindow(app -> window);
  app -> window = NULL;
  SDL_GL_DeleteContext(app -> context);
  app -> context = NULL;
  SDL_Quit();

  printf("\x1b[1A\x1b[0K\x1b[5m\x1B[32mClosed\x1B[0m: \"%s\"\n", app -> title);
  // exit(EXIT_SUCCESS);
}

#endif // NANITE_APPLICATION_IMPLEMENTATION