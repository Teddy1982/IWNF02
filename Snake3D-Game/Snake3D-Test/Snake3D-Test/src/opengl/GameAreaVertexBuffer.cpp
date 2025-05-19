#include "GameAreaVertexBuffer.h"
#include "..\tools\Logger.h"

void GameAreaVertexBuffer::init() {
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVertexVBO);

  glBindVertexArray(mVAO);

  glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Logger::log(2, "%s: VAO and VBO initialized\n", __FUNCTION__);
}

void GameAreaVertexBuffer::cleanup() {
  glDeleteBuffers(1, &mVertexVBO);
  glDeleteVertexArrays(1, &mVAO);
}

void GameAreaVertexBuffer::uploadData(Mesh vertexData) {
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);

  glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(Vertex), &vertexData.vertices.at(0), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GameAreaVertexBuffer::bind() {
  glBindVertexArray(mVAO);
}

void GameAreaVertexBuffer::unbind() {
  glBindVertexArray(0);
}
