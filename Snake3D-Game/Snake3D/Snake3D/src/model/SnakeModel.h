#pragma once

#include "..\opengl\RenderData.h"

class SnakeModel {
public:
    void init(int xpos, int ypos, int zpos);

    MeshBasic getVertexData();

private:
    MeshBasic mVertexData;
};