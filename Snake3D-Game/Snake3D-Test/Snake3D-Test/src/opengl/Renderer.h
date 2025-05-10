#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "..\tools\Timer.h"
#include "..\model\GameArea.h"
#include "..\model\GameOver.h"
#include "Framebuffer.h"
#include "GameAreaVertexBuffer.h"
#include "BasicVertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "UniformBuffer.h"
#include "UserInterface.h"
#include "..\tools\Camera.h"
#include "..\objects\Snake.h"

#include "RenderData.h"

class Renderer {
  public:
    Renderer(GLFWwindow *window);
    ~Renderer();

    Snake mSnake;
    RenderData mRenderData{};

    bool mShowGameOverTex = false;

    bool init(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    void draw();
    void handleKeyEvents(int key, int scancode, int action, int mods);
    void handleMouseButtonEvents(int button, int action, int mods);
    void handleMousePositionEvents(double xPos, double yPos);

    void cleanup();

  private:
    Timer mFrameTimer{};

    Shader mGameAreaShader{};
    Shader mBasicShader{};
    Shader mGameOverShader{};

    Framebuffer mFramebuffer{};
    Texture mTex{};
    Texture mGameOverTex{};
    GameAreaVertexBuffer mGameAreaVertexBuffer{};
    BasicVertexBuffer mBasicVertexBuffer{};
    IndexBuffer mIndexBuffer{};
    UniformBuffer mUniformBuffer{};
    UserInterface* mUserInterface = nullptr;
    Camera mCamera{};

    std::shared_ptr<GameArea> mGameArea = std::shared_ptr<GameArea>();
    std::shared_ptr<GameOver> mGameOver = std::shared_ptr<GameOver>();

    bool mMouseLock = false;
    int mMouseXPos = 0;
    int mMouseYPos = 0;

    double mLastTickTime = 0.0;

    bool mShowMenu = true;

    void handleMovementKeys();

    /* create identity matrix by default */
    glm::mat4 mViewMatrix = glm::mat4(1.0f);
    glm::mat4 mProjectionMatrix = glm::mat4(1.0f);

};
