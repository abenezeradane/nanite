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

#define READER_BUFFSIZE 1024
#define MAX_CONTENT_SIZE 1048576

/**
 * @brief File loading function.
 * 
 * @param filename The filename to load.
 * @return char* The file contents.
 */
char* readfile(char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file)
    return NULL;

  int flag = 0;
  char* shader = (char*) malloc(MAX_CONTENT_SIZE);
  char* buffer = (char*) malloc(READER_BUFFSIZE);
  while (fgets(buffer, READER_BUFFSIZE, file) != NULL)
    strcat(shader, buffer);

  free(buffer);
  fclose(file);
  return shader;
}

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

#ifndef QUEUE_IMPLEMENTATION
#define QUEUE_IMPLEMENTATION

#define QUEUE_MAX 2048

/**
 * @brief The queue structure
 */
typedef struct Queue {
  void** elements;
  unsigned int front, rear;
} Queue;

/**
 * @brief Create an empty queue
 * 
 * @return A queue pointer if successful, NULL if it isn't
 */
Queue* createQueue(void) {
  // Create a queue pointer
  Queue* queue = (Queue*) malloc(sizeof(Queue));

  // Set the queue's front and rear to equal -1
  queue -> front = queue -> rear = -1;

  // Set every element in the queue to NULL
  queue -> elements = (void*) malloc(sizeof(void*) * QUEUE_MAX);

  // Return the empty queue
  return queue;
}

/**
 * @brief Checks if a queue is empty
 * 
 * @param queue The pointer to a queue structure
 * @return true if the queue is empty
 */
bool isEmpty(Queue* queue) {
  // Verify that the queue exists
  if (!queue)
    return true;

  // Returns whether the index of front of the queue is -1
  return queue -> front == -1;
}

/**
 * @brief Checks if a queue is full
 * 
 * @param queue The pointer to a queue structure
 * @return true if the queue is full
 */
bool isFull(Queue* queue) {
  // Verify that the queue exists
  if (!queue)
    return true;

  // Returns whether the index of back of the queue is greater equal to (QUEUE_MAX - 1)
  return queue -> rear == (QUEUE_MAX - 1);
}

/**
 * @brief Add an element into the queue
 * 
 * @param The queue pointer to a queue structure
 * @param element Element to add into the queue
 */
void enqueue(Queue* queue, void* element) {
  // Verify that the queue and element exists and that the queue full
  if (!queue || !element || isFull(queue))
    return;

  // Set the index of the first element to 0
  if (queue -> front == -1)
    queue -> front = 0;

  // Increment the index of the last element
  (queue -> rear)++;

  // Append the element into the queue
  queue -> elements[queue -> rear] = element;
}

/**
 * @brief Removes the front element from the queue
 * 
 * @param The queue pointer to a queue structure
 * @return The pointer to the front element
 */
void* dequeue(Queue* queue) {
  // Verify that the queue exists and isn't empty
  if (!queue || isEmpty(queue))
    return NULL;

  // Get the value of the front element
  void* element = queue -> elements[queue -> front];

  // Increment the index of the first element
  (queue -> front)++;

  // If the queue is now empty, set the index of the first and last elements to -1
  if ((queue -> front) > (queue -> rear))
    queue -> front = queue -> rear = -1;

  // Return the saved value of the front element
  return element;
}

/**
 * @brief Get the pointer of the element in the front of the queue without dequeuing it
 * 
 * @param queue The pointer to a queue structure
 * @return The pointer to the front element
 */
void* peek(Queue* queue) {
  // Verify that the queue exists and isn't empty
  if (!queue || isEmpty(queue))
    return NULL;

  // Return the value of the front element
  return queue -> elements[queue -> front];
}

#endif // QUEUE_IMPLEMENTATION

#ifdef NANITE_IMPLEMENTATION
  #define NANITE_INPUT_IMPLEMENTATION
  #define NANITE_RENDER_IMPLEMENTATION
  #define NANITE_WINDOW_IMPLEMENTATION

  #ifdef NO_NANITE_INPUT
    #undef NANITE_INPUT_IMPLEMENTATION    
  #endif

  #ifdef NO_NANITE_RENDER
    #undef NANITE_RENDERING_IMPLEMENTATION
  #endif

  #ifdef NO_NANITE_WINDOW
    #undef NANITE_WINDOW_IMPLEMENTATION
  #endif
#endif // NANITE_IMPLEMENTATION

#ifndef NANITE_INPUT_INCLUDE
#define NANITE_INPUT_INCLUDE

/**
 * @brief Key enumeration.
 */
// TODO: Add support for mouse and joystick input.
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
 * @brief Key state enumeration.
 */
typedef enum KEY_STATE {
  KEY_STATE_RELEASED,
  KEY_STATE_PRESSED,
  KEY_STATE_HELD
} KEY_STATE;

// Key state array.
static KEY_STATE keystate[KEY_MAX];

/**
 * @brief Check if a key is pressed.
 * 
 * @param key The key to check.
 * @return true if the key is pressed.
 */
bool keypress(KEY key);

/**
 * @brief Initializes the key state array.
 */
static void initKeystates(void);

/**
 * @brief Updates the key state array.
 * 
 * @param keyboard The SDL keyboard event.
 * @param state The state of the key.
 */
static void updateKeystates(uint8_t keyboard, KEY_STATE* state);

/**
 * @brief Processes the SDL keyboard event.
 */
static void processInput(void);

#endif // NANITE_INPUT_INCLUDE

#ifdef NANITE_INPUT_IMPLEMENTATION

/**
 * @brief Check if a key is pressed.
 * 
 * @param key The key to check.
 * @return true if the key is pressed.
 */
bool keypress(KEY key) {
  return keystate[key] != KEY_STATE_RELEASED;
}

/**
 * @brief Initializes the key state array.
 */
static void initKeystates(void) {
  for (int i = 0; i < KEY_MAX; i++) {
    keystate[i] = KEY_STATE_RELEASED;
  }
}

/**
 * @brief Updates the key state array.
 * 
 * @param keyboard The SDL keyboard event.
 * @param state The state of the key.
 */
static void updateKeystates(uint8_t keyboard, KEY_STATE* state) {
  if (keyboard) {
    if (*state > KEY_STATE_RELEASED)
      *state = KEY_STATE_HELD;
    else
      *state = KEY_STATE_PRESSED;
  } else
    *state = KEY_STATE_RELEASED;
}

/**
 * @brief Processes the SDL keyboard event.
 */
static void processInput(void) {
  const uint8_t* state = SDL_GetKeyboardState(NULL);

  // TODO: Update keystate array using configurable key mappings.
  updateKeystates(state[SDL_SCANCODE_W], &keystate[KEY_W]);
  updateKeystates(state[SDL_SCANCODE_A], &keystate[KEY_A]);
  updateKeystates(state[SDL_SCANCODE_S], &keystate[KEY_S]);
  updateKeystates(state[SDL_SCANCODE_D], &keystate[KEY_D]);

  updateKeystates(state[SDL_SCANCODE_ESCAPE], &keystate[KEY_ESCAPE]);
  updateKeystates(state[SDL_SCANCODE_LSHIFT], &keystate[KEY_LSHIFT]);
  updateKeystates(state[SDL_SCANCODE_SPACE], &keystate[KEY_SPACE]);
  updateKeystates(state[SDL_SCANCODE_LALT], &keystate[KEY_LALT]);
}

#endif // NANITE_INPUT_IMPLEMENTATION

#ifndef NANITE_RENDER_INCLUDE
#define NANITE_RENDER_INCLUDE

/**
 * @brief The Entity structure
 */
typedef struct Entity {
  char* ID;
  float position[3];
} Entity;

// Render queues
static Queue* entities;

/**
 * @brief Creates a new entity and enqueues it
 */
void createEntity(char* id, float position[3]);

/**
 * @brief Initialize OpenGL
 */
void initialize(void);

/**
 * @brief Render the scene.
 * 
 * @param window The window to render to.
 */
void render(SDL_Window* window);

#endif // NANITE_RENDER_INCLUDE

#ifdef NANITE_RENDER_IMPLEMENTATION

/**
 * @brief Creates a new entity and enqueues it
 */
void createEntity(char* id, float position[3]) {
  // Verifies the id and position exist
  if (!id || !position)
    return;

  // Creates an Entity pointer
  Entity* entity = (Entity*) malloc(sizeof(Entity));

  // Sets entity data
  entity -> ID = id;
  entity -> position[0] = position[0];
  entity -> position[1] = position[1];
  entity -> position[2] = position[2];

  // Enqueues the entity into the entity queue
  enqueue(entities, entity);
}

/**
 * @brief Initialize OpenGL
 */
void initialize(void) {
  // Initialize GLEW.
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK)
    error(strcat("GLEW Failed to Initialize!\n> ", glewGetErrorString(glewInit())));

  // Initialize render queues
  entities = createQueue();
}

/**
 * @brief Render the scene.
 * 
 * @param window The window to render to.
 */
void render(SDL_Window* window) {
  // Verify that the window isn't null.
  if (!window)
    error("Window pointer is null!");

  // Clear the screen.
  glClearDepth(1.00f);
  glClearColor(0.08f, 0.10f, 0.10f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render the shaders.
  // ...

  // Swap the buffers.
  SDL_GL_SwapWindow(window);
}

#endif // NANITE_RENDER_IMPLEMENTATION

#ifndef NANITE_WINDOW_INCLUDE
#define NANITE_WINDOW_INCLUDE

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
static float now;   // The current time.
static float last;  // The last time.
static float delta; // The time between the current and last frame.

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

#endif // NANITE_WINDOW_INCLUDE

#ifdef NANITE_WINDOW_IMPLEMENTATION

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
  #ifndef NO_NANITE_RENDER
    initialize();
  #endif

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

      // Process input.
      #ifndef NO_NANITE_INPUT
        processInput();
      #endif

      // Call the step function.
      if (app -> step)
        app -> step();

      // Swap the buffers.
      #ifndef NO_NANITE_RENDER
        render(app -> window);
      #else
        SDL_GL_SwapWindow(app -> window);
      #endif

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
  exit(EXIT_SUCCESS);
}

#endif // NANITE_WINDOW_IMPLEMENTATION