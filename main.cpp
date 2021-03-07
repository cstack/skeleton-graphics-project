#include "glad.h"
#include <GLFW/glfw3.h>
#include "simple_graphics_library.h"

#include <iostream>

using namespace SimpleGraphicsLibrary;

void processInput(Window *window);
unsigned int VAOtriangle(float, float);
unsigned int VAOrectangle();
unsigned int VAOtriforce();
unsigned int createVertexShader(const char **);
unsigned int createShaderProgram(unsigned int, unsigned int);

int main() {
  Window *window = initialize(800, 600);
  if (window == NULL) {
    std::cout << "Failed to initalize SimpleGraphicsLibrary" << std::endl;
    return -1;
  }

  while (!window->shouldClose()) {
    if (window->keyIsPressed(GLFW_KEY_ESCAPE)) {
      window->setShouldClose(true);
    }

    window->clear(Color::TEAL);

    window->drawTriangle(-0.5f, 0.0f, Color::ORANGE);
    window->drawTriangle(0.5f, 0.0f, Color::BLUE);
    window->drawRectangle(-0.25, -0.25, 0.5, 0.5, Color::GREEN);

    window->swapBuffers();
    window->pollForEvents();
  }

  window->terminate();
  return 0;
}

unsigned int VAOtriforce() {
  float vertices[] = {
      -1.0f, -1.0f, 0.0f, // left
      0.0f,  -1.0f, 0.0f, // right
      -0.5f, 0.0f,  0.0f, // top
      0.0f,  -1.0f, 0.0f, // left
      1.0f,  -1.0f, 0.0f, // right
      0.5f,  0.0f,  0.0f, // top
      -0.5f, 0.0f,  0.0f, // left
      0.5f,  0.0f,  0.0f, // right
      0.0f,  1.0f,  0.0f  // top
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
