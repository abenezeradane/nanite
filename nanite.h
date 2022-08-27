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

  bool running;           // Whether the application is running.
  bool fullscreen, vsync; // Whether the window is fullscreen and vsync is enabled.
  
  void (*load)(void);     // The function to call when the application is loaded.
  void (*step)(void);     // The function to call when the application is stepped.
} Application;

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
 * @brief Initializes the application.
 * 
 * @param app The application to initialize.
 */
void run(Application* app) {
  // Check if the application is null.
  if (!app)
    error("Application is null.");

  printf("\x1b[5m\x1B[32mInitializing\x1B[0m: \"%s\"\n", app -> title);

  // ...

  printf("\x1b[1A\x1b[0K\x1b[5m\x1B[32mInitialized\x1B[0m: \"%s\"\n", app -> title);

  // ...

  printf("\x1b[5m\x1B[32mRunning\x1B[0m: \"%s\"\n", app -> title);

  // ...

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

  // ...

  printf("\x1b[1A\x1b[0K\x1b[5m\x1B[32mClosed\x1B[0m: \"%s\"\n", app -> title);
  // exit(EXIT_SUCCESS);
}

#endif // NANITE_APPLICATION_IMPLEMENTATION