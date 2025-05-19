#pragma once
#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "..\opengl\Renderer.h"

class Window {
  public:
    bool init(std::string title);
    void mainLoop();
    void cleanup();

  private:
    GLFWwindow *mWindow = nullptr;

    std::unique_ptr<Renderer> mRenderer;
};
