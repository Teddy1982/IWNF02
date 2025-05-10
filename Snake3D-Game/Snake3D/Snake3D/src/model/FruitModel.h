#pragma once

#include "..\opengl\RenderData.h"

class FruitModel {
public:
    void init(int xpos, int ypos, int zpos);

    MeshBasic getVertexData();

private:
    MeshBasic mVertexData;
};