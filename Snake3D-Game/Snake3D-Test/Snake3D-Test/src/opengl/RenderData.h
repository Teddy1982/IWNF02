/* OpenGL */
#pragma once
#include <vector>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 uv;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

struct VertexBasic {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};

struct MeshBasic {
	std::vector<VertexBasic> vertices;
	std::vector<unsigned int> indices;
};

struct RenderData {
  GLFWwindow *rdWindow = nullptr;

  int rdWidth = 0;
  int rdHeight = 0;

  int rdFieldOfView = 60;

  float rdFrameTime = 0.0f;

  int rdMoveForward = 0;
  int rdMoveRight = 0;
  int rdMoveUp = 0;

  float rdTickDiff = 0.0f;

  float rdViewAzimuth = 315.0f;
  float rdViewElevation = -15.0f;

  glm::vec3 rdCameraWorldPosition = glm::vec3(1.3f, 0.5f, 1.3f);
};
