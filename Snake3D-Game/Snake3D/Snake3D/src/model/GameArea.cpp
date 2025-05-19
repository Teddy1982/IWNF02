#include "GameArea.h"
#include "..\tools\Logger.h"

void GameArea::init() {
  mVertexData.vertices.resize(24);

  /* front */
  mVertexData.vertices[0].position = glm::vec3(-0.5f, -0.5f,  0.5f);
  mVertexData.vertices[1].position = glm::vec3(0.5f, -0.5f, 0.5f);
  mVertexData.vertices[2].position = glm::vec3( 0.5f,  0.5f,  0.5f);
  mVertexData.vertices[3].position = glm::vec3(-0.5f,  0.5f,  0.5f);

  mVertexData.vertices[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[3].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[0].uv = glm::vec2(0.0, 0.0);
  mVertexData.vertices[1].uv = glm::vec2(1.0, 0.0);
  mVertexData.vertices[2].uv = glm::vec2(1.0, 1.0);
  mVertexData.vertices[3].uv = glm::vec2(0.0, 1.0);

  /* back */
  mVertexData.vertices[4].position = glm::vec3(0.5f, -0.5f, -0.5f);
  mVertexData.vertices[5].position = glm::vec3(-0.5f, -0.5f,  -0.5f);
  mVertexData.vertices[6].position = glm::vec3(-0.5f,  0.5f,  -0.5f);
  mVertexData.vertices[7].position = glm::vec3( 0.5f,  0.5f,  -0.5f);

  mVertexData.vertices[4].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[5].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[6].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[7].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[4].uv = glm::vec2(0.0, 0.0);
  mVertexData.vertices[5].uv = glm::vec2(1.0, 0.0);
  mVertexData.vertices[6].uv = glm::vec2(1.0, 1.0);
  mVertexData.vertices[7].uv = glm::vec2(0.0, 1.0);

  /* left */
  mVertexData.vertices[8].position = glm::vec3(-0.5f, -0.5f, -0.5f);
  mVertexData.vertices[9].position = glm::vec3(-0.5f, -0.5f,  0.5f);
  mVertexData.vertices[10].position = glm::vec3(-0.5f,  0.5f,  0.5f);
  mVertexData.vertices[11].position = glm::vec3(-0.5f,  0.5f,  -0.5f);

  mVertexData.vertices[8].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[9].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[10].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[11].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[8].uv = glm::vec2(0.0, 0.0);
  mVertexData.vertices[9].uv = glm::vec2(1.0, 0.0);
  mVertexData.vertices[10].uv = glm::vec2(1.0, 1.0);
  mVertexData.vertices[11].uv = glm::vec2(0.0, 1.0);

  /* right */
  mVertexData.vertices[12].position = glm::vec3(0.5f, -0.5f,  0.5f);
  mVertexData.vertices[13].position = glm::vec3(0.5f, -0.5f, -0.5f);
  mVertexData.vertices[14].position = glm::vec3(0.5f,  0.5f,  -0.5f);
  mVertexData.vertices[15].position = glm::vec3(0.5f,  0.5f,  0.5f);

  mVertexData.vertices[12].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[13].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[14].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[15].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[12].uv = glm::vec2(0.0, 0.0);
  mVertexData.vertices[13].uv = glm::vec2(1.0, 0.0);
  mVertexData.vertices[14].uv = glm::vec2(1.0, 1.0);
  mVertexData.vertices[15].uv = glm::vec2(0.0, 1.0);

  /* top */
  mVertexData.vertices[16].position = glm::vec3( 0.5f,  0.5f,  0.5f);
  mVertexData.vertices[17].position = glm::vec3(-0.5f, 0.5f, 0.5f);
  mVertexData.vertices[18].position = glm::vec3(-0.5f,  0.5f,  -0.5f);
  mVertexData.vertices[19].position = glm::vec3( 0.5f,  0.5f,  -0.5f);

  mVertexData.vertices[16].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[17].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[18].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[19].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[16].uv = glm::vec2(1.0f, 0.0f); // unten rechts
  mVertexData.vertices[17].uv = glm::vec2(0.0f, 0.0f); // unten links
  mVertexData.vertices[18].uv = glm::vec2(0.0f, 1.0f); // oben links
  mVertexData.vertices[19].uv = glm::vec2(1.0f, 1.0f); // oben rechts

  /* bottom */
  mVertexData.vertices[20].position = glm::vec3(0.5f, -0.5f, -0.5f);
  mVertexData.vertices[21].position = glm::vec3(-0.5f, -0.5f, -0.5f);
  mVertexData.vertices[22].position = glm::vec3(-0.5f, -0.5f, 0.5f);
  mVertexData.vertices[23].position = glm::vec3( 0.5f,  -0.5f,  0.5f);

  mVertexData.vertices[20].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[21].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[22].color = glm::vec3(1.0f, 1.0f, 1.0f);
  mVertexData.vertices[23].color = glm::vec3(1.0f, 1.0f, 1.0f);

  mVertexData.vertices[20].uv = glm::vec2(1.0f, 0.0f); // unten rechts
  mVertexData.vertices[21].uv = glm::vec2(0.0f, 0.0f); // unten links
  mVertexData.vertices[22].uv = glm::vec2(0.0f, 1.0f); // oben links
  mVertexData.vertices[23].uv = glm::vec2(1.0f, 1.0f); // oben rechts

  Logger::log(2, "%s: loaded %d vertices\n", __FUNCTION__, mVertexData.vertices.size());

  mVertexData.indices = std::initializer_list<unsigned int>{
      0, 1, 2, 2, 3, 0,     //front
      4, 5, 6, 6, 7, 4,     //back
      8, 9, 10, 10, 11, 8,       //left
      12, 13, 14, 14, 15, 12,    //right
      16, 17, 18, 18, 19, 16,    //top
      20, 21, 22, 22, 23, 20 };  //bottom
}

Mesh GameArea::getVertexData() {
  return mVertexData;
}
