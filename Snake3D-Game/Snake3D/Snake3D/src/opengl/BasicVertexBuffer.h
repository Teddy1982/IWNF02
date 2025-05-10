#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderData.h"

class BasicVertexBuffer {
  public:
    void init();
    void uploadData(const std::vector<VertexBasic>& vertices);
    void bind();
    void unbind();
    void cleanup();

  private:
    GLuint mVAO = 0;
    GLuint mVertexVBO = 0;
};
