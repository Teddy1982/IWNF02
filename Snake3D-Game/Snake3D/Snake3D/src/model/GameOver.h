#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "..\opengl\RenderData.h"

class GameOver {
public:
    void init();

    Mesh getVertexData();

private:
    Mesh mVertexData;
};
