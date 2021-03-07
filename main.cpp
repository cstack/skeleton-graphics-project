#include "glad.h"
#include <GLFW/glfw3.h>
#include "simple_graphics_library.h"

#include <iostream>

using namespace SimpleGraphicsLibrary;

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
