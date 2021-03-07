#include "simple_graphics_library.h"
#include <iostream>
#include <sstream>

namespace SimpleGraphicsLibrary {
void framebuffer_size_callback(GLFWwindow *, int, int);

Window *initialize(int width, int height) {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  GLFWwindow *window =
      glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }
  return new Window(window);
}

void Window::terminate() {
  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

Window::Window(GLFWwindow *w) { window = w; }

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::setShouldClose(bool value) {
  glfwSetWindowShouldClose(window, value);
}

bool Window::keyIsPressed(int key) {
  return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::pollForEvents() { glfwPollEvents(); }

void Window::clear(Color_t color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4({0}, {1}, {2}, {3});\n"
                                   "}\n\0";

unsigned int createVertexShader(const char **source) {
  // build and compile our shader program
  // ------------------------------------
  // vertex shader
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, source, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  return vertexShader;
}

unsigned int createShaderProgram(unsigned int vertexShader,
                                 unsigned int fragmentShader) {
  // link shaders
  int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  return shaderProgram;
}

unsigned int VAOtriangle(float xCenter, float yCenter) {
  float vertices[] = {
      xCenter + -0.5f, yCenter + -0.5f, 0.0f, // left
      xCenter + 0.5f,  yCenter + -0.5f, 0.0f, // right
      xCenter + 0.0f,  yCenter + 0.5f,  0.0f  // top
  };

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return VAO;
}

unsigned int VAOrectangle(float topLeftX, float topLeftY, float width,
                          float height) {
  float vertices[] = {
      topLeftX + width, topLeftY,          0.0f, // top right
      topLeftX + width, topLeftY + height, 0.0f, // bottom right
      topLeftX,         topLeftY + height, 0.0f, // bottom left
      topLeftX,         topLeftY,          0.0f  // top left
  };

  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return VAO;
}

unsigned int createFragmentShader(const char **source) {
  // fragment shader
  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, source, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  return fragmentShader;
}

int createShader(Color_t color) {
  std::stringstream ss;
  ss << "#version 330 core\n"
     << "out vec4 FragColor;\n"
     << "void main()\n"
     << "{\n"
     << "   FragColor = vec4(" << color.r << ", " << color.g << ", " << color.b
     << ", " << color.a << ");\n"
     << "}\n\0";
  std::string string = ss.str();
  const char *source = string.c_str();
  return createFragmentShader(&source);
}

void Window::drawTriangle(float xCenter, float yCenter, Color_t color) {
  unsigned int triangle = VAOtriangle(xCenter, yCenter);
  int vertexShader = createVertexShader(&vertexShaderSource);
  int colorShader = createShader(color);
  int colorShaderProgram = createShaderProgram(vertexShader, colorShader);
  glDeleteShader(vertexShader);
  glDeleteShader(colorShader);
  glUseProgram(colorShaderProgram);
  glBindVertexArray(triangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Window::drawRectangle(float topLeftX, float topLeftY, float width,
                           float height, Color_t color) {
  unsigned int square = VAOrectangle(topLeftX, topLeftY, width, height);
  int vertexShader = createVertexShader(&vertexShaderSource);
  int colorShader = createShader(color);
  int colorShaderProgram = createShaderProgram(vertexShader, colorShader);
  glDeleteShader(vertexShader);
  glDeleteShader(colorShader);
  glUseProgram(colorShaderProgram);
  glBindVertexArray(square);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

namespace Color {
const Color_t BLUE = {0.0, 0.0, 1.0, 1.0};
const Color_t TEAL = {0.0, 0.5, 0.5, 1.0};
const Color_t ORANGE = {1.0, 0.65, 0.0, 1.0};
const Color_t GREEN = {0.0, 1.0, 0.0, 1.0};
} // namespace Color

// // glfw: whenever the window size changed (by OS or user resize) this
// callback
// // function executes
// //
// ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//   // make sure the viewport matches the new window dimensions; note that
//   width
//   // and height will be significantly larger than specified on retina
//   displays. glViewport(0, 0, width, height);
// }
} // namespace SimpleGraphicsLibrary
