#include "simple_graphics_library.h"

#include <chrono>
#include <iostream>

namespace Color = SimpleGraphicsLibrary::Color;
typedef std::chrono::high_resolution_clock high_res_clock;

struct state_t {
  double box_x;
  double box_y;
  double triangle_x;
  double triangle_y;
};

void render(SimpleGraphicsLibrary::Window *window, state_t *state) {
  window->clear(Color::TEAL);
  window->drawRectangle(state->box_x, state->box_y, 0.5, 0.5, Color::GREEN);
  window->drawTriangle(state->triangle_x, state->triangle_y, Color::ORANGE);
}

void update(state_t *state, double dt) {
  double new_box_x = state->box_x + 1.0f * dt;
  if (new_box_x > 1) {
    new_box_x -= 2;
  }
  state->box_x = new_box_x;

  double new_triangle_y = state->triangle_y + 1.0f * dt;
  if (new_triangle_y > 1) {
    new_triangle_y -= 2;
  }
  state->triangle_y = new_triangle_y;
}

void initialize_state(state_t *state) {
  state->box_x = 0.0;
  state->box_y = 0.0;
  state->triangle_x = 0.0;
  state->triangle_y = 0.0;
}

int main() {
  SimpleGraphicsLibrary::Window *window =
      SimpleGraphicsLibrary::initialize(800, 600);
  if (window == NULL) {
    std::cout << "Failed to initalize SimpleGraphicsLibrary" << std::endl;
    return -1;
  }

  state_t state;
  initialize_state(&state);

  high_res_clock::time_point t1 = high_res_clock::now();
  while (!window->shouldClose()) {
    high_res_clock::time_point t2 = high_res_clock::now();
    std::chrono::duration<double> duration = t2 - t1;
    double dt = duration.count();
    t1 = t2;

    if (window->keyIsPressed(GLFW_KEY_ESCAPE)) {
      window->setShouldClose(true);
    }

    update(&state, dt);
    render(window, &state);

    window->swapBuffers();
    window->pollForEvents();
  }

  window->terminate();
  return 0;
}
