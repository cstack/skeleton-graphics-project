#include "glad.h"
#include <GLFW/glfw3.h>

namespace SimpleGraphicsLibrary {
  struct Color_t {
    double r;
    double g;
    double b;
    double a;
  };
  namespace Color {
    extern const Color_t BLUE;
    extern const Color_t TEAL;
    extern const Color_t ORANGE;
    extern const Color_t GREEN;
  }
  class Window {
    GLFWwindow *window;
  public:
    Window(GLFWwindow *);
    void clear(Color_t);
    bool shouldClose();
    void setShouldClose(bool);
    void terminate();
    bool keyIsPressed(int);
    void swapBuffers();
    void pollForEvents();
    void drawTriangle(float xCenter, float yCenter, Color_t color);
    void drawRectangle(float topLeftX, float topLeftY, float width, float height, Color_t color);
  };
  Window *initialize(int, int);
}