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
char* readfile(const char* filename) {
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
 * @brief Get the capacity of the queue
 * 
 * @param queue The pointer to a queue structure
 * @return The size of the queue
 */
unsigned int queueSize(Queue* queue) {
  // Verify that the queue exists
  if (!queue)
    return true;

  // Return the size of the queue
  if (isEmpty(queue))           
    return 0;                     // Return 0 if the queue is empty
  else if (isFull)
    return QUEUE_MAX;             // Return QUEUE_MAX if the queue is full
  else
    return (queue -> rear) + 1;   // Return the difference between front and rear index + 1
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

#ifndef HASHMAP_IMPLEMENTATION
#define HASHMAP_IMPLEMENTATION

#define MAP_MAX 2048

// Define HashMap
typedef void** HashMap;

/**
 * @brief Create an empty hash map
 * 
 * @return A hash map pointer if successful, NULL if it isn't
 */
HashMap* createHashMap(void) {
  return (HashMap*) malloc(sizeof(HashMap) * MAP_MAX);
}

/**
 * @brief Hash a string
 * 
 * @param key String to hash
 * @return An unsigned int for the hash code
 */
unsigned int hash(char* key) {
  // Calculate the alpha by the sum of ASCII values of characters multiplied by their respective order in the string
  register unsigned int itr, alpha = 0;
  for (itr = 0; itr < strlen(key); itr++)
    alpha += ((int) key[itr]) * (itr + 1);

  // Return the modulus of the alpha and a prime number
  return alpha % 2069;
}

/**
 * @brief Insert an element into the hash map
 * 
 * @param map The hash map
 * @param key The key to the element
 * @param element The element to be inserted
 */
void insert(HashMap* map, char* key, void* element) {
  // Verify that the map, the key, and the element exist
  if (!map || !key || !element)
    return;

  // Get the hash code of the key
  unsigned int index = hash(key);

  // Insert the element at the index value (exit if collision)
  if (!map[index])
    map[index] = element;
  else
    return;
}

/**
 * @brief Search for an element into the hash map
 * 
 * @param map The hash map
 * @param key The key to the element
 * @return The pointer to the element in the hash map
 */
void* search(HashMap* map, char* key) {
  // Verify that the map and the key exist
  if (!map || !key)
    return NULL;

  // Get the hash code of the key
  unsigned int index = hash(key);

  // Return the element in the hash map at that index
  return map[index];
}

/**
 * @brief Delete an element from the hash map
 * 
 * @param map The hash map
 * @param key The key to the element
 */
void delete(HashMap* map, char* key) {
  // Verify that the map and the key exist
  if (!map || !key)
    return;

  // Get the hash code of the key
  unsigned int index = hash(key);

  // Make the element at that index NULL
  map[index] = NULL;
}

#endif // HASHMAP_IMPLEMENTATION

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
  const char* ID;
  float position[3];
} Entity;

/**
 * @brief The Shader structure
 */
typedef struct Shader {
  GLuint program;
  GLuint vao, vbo, ebo;
  Entity* entity;
} Shader;

// Render field variables
static Queue* shaders;              // Queue of living shaders
static HashMap* entities;           // HashMap of living entities

static float vertices[] = {         // The vertices of the triangle.
   0.10f,  0.10f, 0.00f,            // top right
   0.10f, -0.10f, 0.00f,            // bottom right
  -0.10f, -0.10f, 0.00f,            // bottom left
  -0.10f,  0.10f, 0.00f             // top left 
};

static unsigned int indices[] = {   // The indices of the triangles
  0, 1, 3,                          // first Triangle
  1, 2, 3                           // second Triangle
};

/**
 * @brief Creates a new entity and appends it
 * 
 * @param ID A string containing the entity's id
 * @param position The position of the entity on the screen
 */
void createEntity(char* ID, float position[3]);

/**
 * @brief Get the pointer of an entity from it's ID
 * 
 * @param ID An entity ID
 * @return A pointer to the entity
 */
Entity* getEntity(char* ID);

/**
 * @brief Get entity position
 * 
 * @param ID The entity ID
 * @return An array containing the entity's coordinates
 */
float* getEntityPosition(char* ID);

/**
 * @brief Update entity position
 * 
 * @param ID The entity ID
 * @param delta The changed in position
 */
void updateEntityPosition(char* ID, float delta[3]);

/**
 * @brief Creates a new shader and enqueues it
 * 
 * @param entity Pointer to an entity
 * @param vertFile Vertex shader filename
 * @param fragFile Fragment shader filename
 */
void createShader(Entity* entity, const char* vertFile, const char* fragFile);

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
 * 
 * @param ID A string containing the entity's id
 * @param position The position of the entity on the screen
 */
void createEntity(char* ID, float position[3]) {
  // Verify that the id and position exist
  if (!ID || !position)
    return;

  // Creates an Entity pointer
  Entity* entity = (Entity*) malloc(sizeof(Entity));

  // Sets entity data
  entity -> ID = ID;
  entity -> position[0] = position[0];
  entity -> position[1] = position[1];
  entity -> position[2] = position[2];

  // Appends the entity into the entity map
  insert(entities, ID, entity);
}

/**
 * @brief Get the pointer of an entity from it's ID
 * 
 * @param ID An entity ID
 * @return A pointer to the entity
 */
Entity* getEntity(char* ID) {
  // Verifies the id exists
  if (!ID)
    return NULL;

  // Search the hash map and return the result
  return search(entities, ID);
}

/**
 * @brief Get entity position
 * 
 * @param ID The entity ID
 * @return An array containing the entity's coordinates
 */
float* getEntityPosition(char* ID) {
  // Verifies the id exists
  if (!ID)
    return NULL;

  // Get the entity from the hash map, if it exists
  Entity* entity = getEntity(ID);
  if (!entity)
    return NULL;

  // Return the entity's position
  return (float[3]) {entity -> position[0], entity -> position[1], entity -> position[2]};
}

/**
 * @brief Update entity position
 * 
 * @param ID The entity ID
 * @param delta The changed in position
 */
void updateEntityPosition(char* ID, float delta[3]) {
  // Verify that the id and delta exist
  if (!ID || !delta)
    return;

  // Get the entity from the hash map, if it exists
  Entity* entity = getEntity(ID);
  if (!entity)
    return;

  // Update the entity's position
  entity -> position[0] += delta[0];
  entity -> position[1] += delta[1];
  entity -> position[2] += delta[2];
}

/**
 * @brief Creates a new shader and enqueues it
 * 
 * @param entity Pointer to an entity
 * @param vertFile Vertex shader filename
 * @param fragFile Fragment shader filename
 */
void createShader(Entity* entity, const char* vertFile, const char* fragFile) {
  // Verify that the entity and filenames exist
  if (!entity || !vertFile || !fragFile)
    return;

  // Create the shader
  Shader* shader = (Shader*) malloc(sizeof(Shader));

  // Generate the vertex array
  glGenVertexArrays(1, &(shader -> vao));
  if (shader -> vao == 0)
    error("Failed to create vertex array object!");

    // Create the vertex array object.
  glGenVertexArrays(1, &(shader -> vao));
  if (shader -> vao == 0)
    error("Failed to create vertex array object!");

  // Create the vertex buffer object.
  glGenBuffers(1, &(shader -> vbo));
  if (shader -> vbo == 0)
    error("Failed to create vertex buffer object!");

  // Create the element buffer object.
  glGenBuffers(1, &(shader -> ebo));
  if (shader -> ebo == 0)
    error("Failed to create element buffer object!");

  // Bind the vertex array object.
  glBindVertexArray(shader -> vao);

  // Bind the vertex buffer object.
  glBindBuffer(GL_ARRAY_BUFFER, shader -> vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to bind vertex buffer object!");

  // Bind the element buffer object.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader -> ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to bind element buffer object!");

  // Set the vertex attribute pointers.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Create the vertex shader.
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  if (vertShader == 0)
    error("Failed to create vertex shader!");

  // Load the vertex shader.
  char* vertSource = readfile(vertFile);
  if (vertSource == NULL)
    error("Failed to read vertex shader file!");

  // Compile the vertex shader.
  glShaderSource(vertShader, 1, (const char**) &vertSource, NULL);
  glCompileShader(vertShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to compile vertex shader!");

  // Create the fragment shader.
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (fragShader == 0)
    error("Failed to create fragment shader!");

  // Load the fragment shader.
  char* fragSource = readfile(fragFile);
  if (fragSource == NULL)
    error("Failed to read fragment shader file!");

  // Compile the fragment shader.
  glShaderSource(fragShader, 1, (const char**) &fragSource, NULL);
  glCompileShader(fragShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to compile fragment shader!");

  // Create the shader program.
  shader -> program = glCreateProgram();
  if (shader -> program == 0)
    error("Failed to create shader program!");

  // Attach the vertex shader.
  glAttachShader(shader -> program, vertShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to attach vertex shader!");

  // Attach the fragment shader.
  glAttachShader(shader -> program, fragShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to attach fragment shader!");

  // Link the shader program.
  glLinkProgram(shader -> program);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to link shader program!");

  // Delete the vertex shader.
  glDeleteShader(vertShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to delete vertex shader!");

  // Delete the fragment shader.
  glDeleteShader(fragShader);
  if (glGetError() != GL_NO_ERROR)
    error("Failed to delete fragment shader!");

  // Add shader to queue
  enqueue(shaders, shader);
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

  // Initialize render field variables
  shaders = createQueue();
  entities = createHashMap();
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
  if (!isEmpty(shaders)) {  // Verify that the shader queue isn't empty
    register int itr;
    for (itr = 0; itr < queueSize(shaders); itr++) {
      // Dequeue the shader
      Shader* shader = dequeue(shaders);

      // Use the shader program
      glUseProgram(shader -> program);
      if (glGetError() != GL_NO_ERROR)
        error("Failed to use shader program!");

      // Set the shader position.
      glUniform3fv(glGetUniformLocation(shader -> program, "position"), 1, shader -> entity -> position);
      if (glGetError() != GL_NO_ERROR)
        error("Failed to set shader position!");

      // Bind the vertex array object.
      glBindVertexArray(shader -> vao);
      if (glGetError() != GL_NO_ERROR)
        error("Failed to bind vertex array object!");
      
      // Draw the triangles.
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      if (glGetError() != GL_NO_ERROR)
        error("Failed to draw elements!");

      // Enqueue the shader
      enqueue(shaders, shader);
    }
  }

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