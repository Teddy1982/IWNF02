/* Dear ImGui*/
#pragma once

#include "RenderData.h"

class Renderer;

class UserInterface {
  public:
    UserInterface(Renderer& renderer);
    void init(RenderData &renderData);
    void createFrame(RenderData &renderData);
    void render();
    void cleanup();

private:
    Renderer& mRenderer;

    bool mShowHighscoreInput = false;
};
