#include "Window.h"
#include "..\tools\Logger.h"
#include "..\opengl\Controls.h"

bool Window::init(std::string title) {
  if (!glfwInit()) {
    Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
    return false;
  }

  /* set a "hint" for the NEXT window created*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  int screenWidth = mode->width;
  int screenHeight = mode->height;

  mWindow = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), monitor, nullptr);

  if (!mWindow) {
    glfwTerminate();
    Logger::log(1, "%s error: Could not create window\n", __FUNCTION__);
    return false;
  }

  glfwMakeContextCurrent(mWindow);

  mRenderer = std::make_unique<Renderer>(mWindow);

  glfwSetWindowUserPointer(mWindow, mRenderer.get());
  glfwSetWindowSizeCallback(mWindow, [](GLFWwindow *win, int screenWidth, int screenHeight) {
      auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
      renderer->setSize(screenWidth, screenHeight);
    }
  );

  glfwSetKeyCallback(mWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
      auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
      renderer->handleKeyEvents(key, scancode, action, mods);
    }
  );

  glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *win, int button, int action, int mods) {
      auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
      renderer->handleMouseButtonEvents(button, action, mods);
    }
  );

  glfwSetCursorPosCallback(mWindow, [](GLFWwindow *win, double xpos, double ypos) {
      auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
      renderer->handleMousePositionEvents(xpos, ypos);
    }
  );

  if (!mRenderer->init(screenWidth, screenHeight)) {
    glfwTerminate();
    Logger::log(1, "%s error: Could not init OpenGL\n", __FUNCTION__);
    return false;
  }

  Logger::log(1, "%s: Window with OpenGL 4.6 successfully initialized\n", __FUNCTION__);
  return true;
}


void Window::mainLoop() {
  while (!glfwWindowShouldClose(mWindow)) {
    mRenderer->draw();

    /* swap buffers */
    glfwSwapBuffers(mWindow);

    /* poll events in a loop */
    glfwPollEvents();
  }
}

void Window::cleanup() {
  mRenderer->cleanup();

  glfwDestroyWindow(mWindow);
  glfwTerminate();
  Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
}
