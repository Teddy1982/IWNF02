#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "..\opengl\RenderData.h"

class GameArea {
  public:
    void init();

    Mesh getVertexData();

  private:
    Mesh mVertexData;
};
