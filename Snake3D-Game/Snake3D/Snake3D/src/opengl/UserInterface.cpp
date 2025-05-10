#include <string>

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "UserInterface.h"
#include "..\opengl\Renderer.h"
#include "..\opengl\Controls.h"


Controls gControls;
RebindContext rebindContext;

UserInterface::UserInterface(Renderer& renderer) : mRenderer(renderer) {}

void UserInterface::init(RenderData &renderData) {
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(renderData.rdWindow, true);

  const char *glslVersion = "#version 460 core";
  ImGui_ImplOpenGL3_Init(glslVersion);

  ImGui::StyleColorsDark();

  mShowHighscoreInput = false;
}

void UserInterface::createFrame(RenderData &renderData) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGuiWindowFlags imguiWindowFlags = 0;
  imguiWindowFlags |= ImGuiWindowFlags_NoCollapse;
  //imguiWindowFlags |= ImGuiWindowFlags_NoResize;
  //imguiWindowFlags |= ImGuiWindowFlags_NoMove;

  if (mRenderer.mSnake.mIsGameOver) {
	  std::vector<HighscoreEntry> entries = mRenderer.mSnake.mHighscore.loadTop10();
	  int score = mRenderer.mSnake.mScore;
	  bool isNewEntry = (entries.size() < 10);

	  if (!isNewEntry) {
		  for (const auto& entry : entries) {
			  if (score > entry.score) {
				  isNewEntry = true;
				  break;
			  }
		  }
	  }

	  if (isNewEntry) {
		  mShowHighscoreInput = true;
	  }
	  mRenderer.mShowGameOverTex = true;
	  mRenderer.mSnake.mIsGameOver = false;
  }

  if (mShowHighscoreInput) {
	  ImGui::SetNextWindowPos(ImVec2(renderData.rdWidth / 2 - 175, 60));
	  ImGui::SetNextWindowSize(ImVec2(350, 80));
	  ImGui::Begin("Highscore");

	  static char buffer[64] = "";
	  ImGui::Text("New Highscore! Please type your name:");
	  if (ImGui::InputText(" ", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
		  mRenderer.mSnake.mHighscore.addEntry(std::string(buffer), mRenderer.mSnake.mScore);
		  buffer[0] = '\0';
		  mShowHighscoreInput = false;
	  }

	  ImGui::End();
  }

  ImGui::SetNextWindowBgAlpha(0.8f);
  ImGui::SetNextWindowSize(ImVec2(400, 600));

  ImGui::Begin("Snake3D");

  ImGui::SetWindowFontScale(3.0f);
  ImGui::Text("Score: %i", mRenderer.mSnake.mScore);
  ImGui::SetWindowFontScale(1.0f);

  if (ImGui::CollapsingHeader("Camera & Window Status")) {
	  ImGui::Text("Camera Position:");
	  ImGui::SameLine();
	  ImGui::Text("%s", glm::to_string(renderData.rdCameraWorldPosition).c_str());

	  ImGui::Text("View Azimuth:");
	  ImGui::SameLine();
	  ImGui::Text("%s", std::to_string(renderData.rdViewAzimuth).c_str());

	  ImGui::Text("View Elevation:");
	  ImGui::SameLine();
	  ImGui::Text("%s", std::to_string(renderData.rdViewElevation).c_str());

	  ImGui::Separator();

	  std::string windowDims = std::to_string(renderData.rdWidth) + "x" + std::to_string(renderData.rdHeight);
	  ImGui::Text("Window Dimensions:");
	  ImGui::SameLine();
	  ImGui::Text("%s", windowDims.c_str());

	  std::string imgWindowPos = std::to_string(static_cast<int>(ImGui::GetWindowPos().x)) + "/" + std::to_string(static_cast<int>(ImGui::GetWindowPos().y));
	  ImGui::Text("ImGui Window Position:");
	  ImGui::SameLine();
	  ImGui::Text("%s", imgWindowPos.c_str());
  }


  if (ImGui::CollapsingHeader("Game")) {
	  if (ImGui::Button("New Game", ImVec2(400, 50))) {
		  mRenderer.mShowGameOverTex = false;
		  mRenderer.mSnake.init();
	  } 

	  if (ImGui::Button("Exit", ImVec2(400, 50))) {
		  glfwSetWindowShouldClose(renderData.rdWindow, true);
	  }
  }

  if (ImGui::CollapsingHeader("Audio")) {
	  ImGui::Checkbox("Music on", &mRenderer.mSnake.mIsPlayingMusic);
	  ImGui::Checkbox("Sound on", &mRenderer.mSnake.mIsPlayingSound);
  }

  if (ImGui::CollapsingHeader("Controls")) {
	  static KeyBindings editableBindings = gControls.getKeyBindings();

	  auto showRebindButton = [&](const char* label, int* keyPtr) {
		  std::string buttonLabel = std::string(label) + ": " + gControls.getKeyDisplayName(*keyPtr);
		  if (ImGui::Button(buttonLabel.c_str(), ImVec2(200, 30))) {
			  rebindContext.awaitingKey = true;
			  rebindContext.actionName = label;
			  rebindContext.targetKey = keyPtr;
		  }
	  };

	  if (rebindContext.awaitingKey) {
		  ImGui::Text("Press a key for: %s", rebindContext.actionName.c_str());
	  }

	  showRebindButton("Move camera up", &editableBindings.cameraUp);
	  showRebindButton("Move camera down", &editableBindings.cameraDown);
	  showRebindButton("Move camera left", &editableBindings.cameraLeft);
	  showRebindButton("Move camera right", &editableBindings.cameraRight);
	  showRebindButton("Move camera forward", &editableBindings.cameraForward);
	  showRebindButton("Move camera backward", &editableBindings.cameraBackward);
	  showRebindButton("Move up", &editableBindings.up);
	  showRebindButton("Move down", &editableBindings.down);
	  showRebindButton("Move left", &editableBindings.left);
	  showRebindButton("Move right", &editableBindings.right);
	  showRebindButton("Move forward", &editableBindings.forward);
	  showRebindButton("Move backward", &editableBindings.backward);
	  showRebindButton("Pause", &editableBindings.pause);

	  if (ImGui::Button("Save control settings", ImVec2(200, 50))) {
		  gControls.setKeyBindings(editableBindings);
		  gControls.saveBindings();
	  }
  }

  bool isVisible = false;
  if (ImGui::CollapsingHeader("Highscore")) {
	  isVisible = true;

	  std::vector<HighscoreEntry> entries = mRenderer.mSnake.mHighscore.loadTop10();

	  if (isVisible) {
		  ImGui::SetNextWindowPos(ImVec2(renderData.rdWidth / 2 - 200, 60));
		  ImGui::SetNextWindowSize(ImVec2(400, 600));
		  ImGui::Begin("Highscores");
		  for (const auto entry : entries) {
			  ImGui::Text("Date: %s", entry.date.c_str());
			  ImGui::Text("Score: %d", entry.score);
			  ImGui::Text("Name: %s", entry.name.c_str());
			  ImGui::Separator();
		  }

		  ImGui::End();
	  }
  }

  ImGui::End();
}

void UserInterface::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::cleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
