#include <algorithm>

#include <imgui_impl_glfw.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "..\tools\Logger.h"
#include "Controls.h"

extern Controls gControls;
extern RebindContext rebindContext;


Renderer::Renderer(GLFWwindow* window) {
  mRenderData.rdWindow = window;
  mUserInterface = new UserInterface(*this);
  gControls.loadBindings();
}

Renderer::~Renderer() {
    delete mUserInterface;
}

bool Renderer::init(unsigned int width, unsigned int height) {
  /* required for perspective */
  mRenderData.rdWidth = width;
  mRenderData.rdHeight = height;

  /* initalize GLAD */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::log(1, "%s error: failed to initialize GLAD\n", __FUNCTION__);
    return false;
  }

  if (!GLAD_GL_VERSION_4_6) {
    Logger::log(1, "%s error: failed to get at least OpenGL 4.6\n", __FUNCTION__);
    return false;
  }

  GLint majorVersion, minorVersion;
  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
  Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);

  if (!mFramebuffer.init(width, height)) {
    Logger::log(1, "%s error: could not init Framebuffer\n", __FUNCTION__);
    return false;
  }
  Logger::log(1, "%s: framebuffer succesfully initialized\n", __FUNCTION__);

  if (!mTex.loadTexture("src/textures/Playground.png")) {
    Logger::log(2, "%s: playground texture loading failed\n", __FUNCTION__);
    return false;
  }
  Logger::log(1, "%s: playground texture successfully loaded\n", __FUNCTION__);

 
  if (!mGameOverTex.loadTexture("src/textures/GameOver.png")) {
      Logger::log(1, "%s: game over texture loading failed\n", __FUNCTION__);
      return false;
  }
  Logger::log(1, "%s: game over texture successfully loaded\n", __FUNCTION__);
  
  mGameAreaVertexBuffer.init();
  Logger::log(1, "%s: gamearea vertex buffer successfully created\n", __FUNCTION__);

  mBasicVertexBuffer.init();
  Logger::log(1, "%s: basic vertex buffer successfully created\n", __FUNCTION__);

  mIndexBuffer.init();
  Logger::log(1, "%s: basic index buffer successfully created\n", __FUNCTION__);

  mUniformBuffer.init();
  Logger::log(1, "%s: uniform buffer successfully created\n", __FUNCTION__);

  if (!mGameAreaShader.loadShaders("src/shader/gameArea.vert", "src/shader/gameArea.frag")) {
    Logger::log(1, "%s: gameArea shader loading failed\n", __FUNCTION__);
    return false;
  }

  if (!mGameOverShader.loadShaders("src/shader/gameOver.vert", "src/shader/gameOver.frag")) {
      Logger::log(1, "%s: gameOver shader loading failed\n", __FUNCTION__);
      return false;
  }

  if (!mBasicShader.loadShaders("src/shader/basicShader.vert", "src/shader/basicShader.frag")) {
      Logger::log(1, "%s: basic shader loading failed\n", __FUNCTION__);
      return false;
  }
  Logger::log(1, "%s: shaders succesfully loaded\n", __FUNCTION__);

  mUserInterface->init(mRenderData);
  Logger::log(1, "%s: user interface initialized\n", __FUNCTION__);

  mGameArea = std::make_shared<GameArea>();
  mGameArea->init();

  mSnake.init();

  mGameOver = std::make_shared<GameOver>();
  mGameOver->init();

  glEnable(GL_DEPTH_TEST);

  return true;
}

void Renderer::setSize(unsigned int width, unsigned int height) {
  /* handle minimize */
  if (width == 0 || height == 0) {
    return;
  }

  mRenderData.rdWidth = width;
  mRenderData.rdHeight = height;

  mFramebuffer.resize(width, height);
  glViewport(0, 0, width, height);

  Logger::log(2, "%s: resized window to %dx%d\n", __FUNCTION__, width, height);
}

void Renderer::handleMouseButtonEvents(int button, int action, int mods) {
  /* forward to ImGui */
  ImGuiIO& io = ImGui::GetIO();
  if (button >= 0 && button < ImGuiMouseButton_COUNT) {
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);
  }

  /* hide from application if above ImGui window */
  if (io.WantCaptureMouse) {
    return;
  }

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    mMouseLock = !mMouseLock;

    if (mMouseLock) {
      glfwSetInputMode(mRenderData.rdWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      /* enable raw mode if possible */
      if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(mRenderData.rdWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
      }
    } else {
      glfwSetInputMode(mRenderData.rdWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }
}

void Renderer::handleMousePositionEvents(double xPos, double yPos){
  /* forward to ImGui */
  ImGuiIO& io = ImGui::GetIO();
  io.AddMousePosEvent((float)xPos, (float)yPos);

  /* hide from application if above ImGui window */
  if (io.WantCaptureMouse) {
    return;
  }

  /* calculate relative movement from last position */
  int mouseMoveRelX = static_cast<int>(xPos) - mMouseXPos;
  int mouseMoveRelY = static_cast<int>(yPos) - mMouseYPos;

  if (mMouseLock) {
    mRenderData.rdViewAzimuth += mouseMoveRelX / 10.0;
    /* keep between 0 and 360 degree */
    if (mRenderData.rdViewAzimuth < 0.0) {
      mRenderData.rdViewAzimuth += 360.0;
    }
    if (mRenderData.rdViewAzimuth >= 360.0) {
      mRenderData.rdViewAzimuth -= 360.0;
    }

    mRenderData.rdViewElevation -= mouseMoveRelY / 10.0;
    /* keep between -89 and +89 degree */
    if (mRenderData.rdViewElevation > 89.0) {
      mRenderData.rdViewElevation = 89.0;
    }
    if (mRenderData.rdViewElevation < -89.0) {
      mRenderData.rdViewElevation = -89.0;
    }
  }

  /* save old values*/
  mMouseXPos = static_cast<int>(xPos);
  mMouseYPos = static_cast<int>(yPos);
}

void Renderer::handleMovementKeys() {
  gControls.update(mRenderData.rdWindow);
  const InputState& input = gControls.getInputState();

  mRenderData.rdMoveForward = 0;
  
  if (input.cameraForward) {
      mRenderData.rdMoveForward += 1;
  }
  if (input.cameraBackward) {
      mRenderData.rdMoveForward -= 1;
  }

  mRenderData.rdMoveRight = 0;
  if (input.cameraLeft) {
      mRenderData.rdMoveRight -= 1;
  }
  if (input.cameraRight) {
      mRenderData.rdMoveRight += 1;
  }

  mRenderData.rdMoveUp = 0;
  if (input.cameraUp) {
      mRenderData.rdMoveUp += 1;
  }
  if (input.cameraDown) {
      mRenderData.rdMoveUp -= 1;
  }

  if (input.moveForward) {
      if (mSnake.mDirection != Direction::backward) {
          mSnake.mDirection = Direction::forward;
      }
  }
  if (input.moveBackward) {
      if (mSnake.mDirection != Direction::forward) {
          mSnake.mDirection = Direction::backward;
      }
  }
  if (input.moveLeft) {
      if (mSnake.mDirection != Direction::right) {
          mSnake.mDirection = Direction::left;
      }
  }
  if (input.moveRight) {
      if (mSnake.mDirection != Direction::left) {
          mSnake.mDirection = Direction::right;
      }
  }
  if (input.moveDown) {
      if (mSnake.mDirection != Direction::up) {
          mSnake.mDirection = Direction::down;
      }
  }
  if (input.moveUp) {
      if (mSnake.mDirection != Direction::down) {
          mSnake.mDirection = Direction::up;
      }
  }
  if (input.pause) {
      mSnake.mDirection = Direction::pause;
  }
}

void Renderer::handleKeyEvents(int key, int scancode, int action, int mods) {
    if (glfwGetKey(mRenderData.rdWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        mShowMenu = !mShowMenu;
    }
    if (rebindContext.awaitingKey && action == GLFW_PRESS) {
        if (rebindContext.targetKey) {
            *rebindContext.targetKey = key;
        }
        rebindContext.awaitingKey = false;
        rebindContext.targetKey = nullptr;
    }
    else {
        gControls.keyCallback(key, action);
    }
}


void Renderer::draw() {
  /* handle minimize */
  while (mRenderData.rdWidth == 0 || mRenderData.rdHeight == 0) {
    glfwGetFramebufferSize(mRenderData.rdWindow, &mRenderData.rdWidth, &mRenderData.rdHeight);
    glfwWaitEvents();
  }

  /* get time difference for movement */
  double tickTime = glfwGetTime();
  mRenderData.rdTickDiff = tickTime - mLastTickTime;

  mRenderData.rdFrameTime = mFrameTimer.stop();
  mFrameTimer.start();

  handleMovementKeys();

  /* draw to framebuffer */
  mFramebuffer.bind();

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float t = glfwGetTime();
  glm::mat4 world = glm::mat4(1.0f);

  mBasicShader.use();

  glEnable(GL_CULL_FACE);

  static int duration = mSnake.mLevel;
  duration--;
    
  if (duration <= 0) {
      duration = mSnake.mLevel;
      if (mSnake.mIsRunning) {
          mSnake.update();
      }
  }
  
  unsigned int indexOffset = 0;

  std::unique_ptr<MeshBasic> snakeMesh = std::make_unique<MeshBasic>();
  for (const auto& segment : *mSnake.mSnakeModel) {
      if (!segment) continue; // Safety check
      MeshBasic data = segment->getVertexData();

      snakeMesh->vertices.insert(
          snakeMesh->vertices.end(),
          data.vertices.begin(),
          data.vertices.end()
      );

      for (unsigned int i : data.indices) {
          snakeMesh->indices.push_back(i + indexOffset);
      }

      indexOffset += data.vertices.size();
  }

  mBasicVertexBuffer.uploadData(snakeMesh->vertices);
  mIndexBuffer.uploadData(snakeMesh->indices);

  mBasicVertexBuffer.bind();
  mIndexBuffer.bind();

  mIndexBuffer.draw(GL_TRIANGLES, mIndexBuffer.getCount());
  mBasicVertexBuffer.unbind();
  mIndexBuffer.unbind();

  mBasicVertexBuffer.uploadData(mSnake.mFruitModel->getVertexData().vertices);
  mIndexBuffer.uploadData(mSnake.mFruitModel->getVertexData().indices);

  mBasicVertexBuffer.bind();
  mIndexBuffer.bind();

  mIndexBuffer.draw(GL_TRIANGLES, mIndexBuffer.getCount());

  mBasicVertexBuffer.unbind();
  mIndexBuffer.unbind();

  mGameAreaShader.use();

  mProjectionMatrix = glm::perspective(glm::radians(static_cast<float>(mRenderData.rdFieldOfView)), static_cast<float>(mRenderData.rdWidth) / static_cast<float>(mRenderData.rdHeight), 0.01f, 50.0f);
  mViewMatrix = mCamera.getViewMatrix(mRenderData) * world;

  mUniformBuffer.uploadUboData(mViewMatrix, mProjectionMatrix);

  mGameAreaVertexBuffer.uploadData(mGameArea->getVertexData());
  mIndexBuffer.uploadData(mGameArea->getVertexData().indices);

  glDisable(GL_CULL_FACE);
  
  mTex.bind();
  mGameAreaVertexBuffer.bind();
  mIndexBuffer.bind();
  mIndexBuffer.draw(GL_TRIANGLES, mIndexBuffer.getCount());
  mGameAreaVertexBuffer.unbind();
  mIndexBuffer.unbind();
  mTex.unbind();
  
  if (mShowGameOverTex) {
      mGameOverShader.use();

      mGameAreaVertexBuffer.uploadData(mGameOver->getVertexData());
      mIndexBuffer.uploadData(mGameOver->getVertexData().indices);

      mGameOverTex.bind();
      mGameAreaVertexBuffer.bind();
      mIndexBuffer.bind();
      mIndexBuffer.draw(GL_TRIANGLES, mIndexBuffer.getCount());
      mGameAreaVertexBuffer.unbind();
      mIndexBuffer.unbind();
      mGameOverTex.unbind();
  }
  
  mFramebuffer.unbind();

  /* blit color buffer to screen */
  mFramebuffer.drawToScreen();

  if (mShowMenu) {
      mUserInterface->createFrame(mRenderData);
      mUserInterface->render();
  }

  mLastTickTime = tickTime;
}

void Renderer::cleanup() {
  mUserInterface->cleanup();
  mGameAreaShader.cleanup();
  mBasicShader.cleanup();
  mTex.cleanup();
  mGameAreaVertexBuffer.cleanup();
  mBasicVertexBuffer.cleanup();
  mIndexBuffer.cleanup();
  mUniformBuffer.cleanup();
  mFramebuffer.cleanup();
}
