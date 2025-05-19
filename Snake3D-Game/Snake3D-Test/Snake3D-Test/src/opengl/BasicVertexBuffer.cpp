#include "BasicVertexBuffer.h"
#include "..\tools\Logger.h"

void BasicVertexBuffer::init() {
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVertexVBO);

  glBindVertexArray(mVAO);

  glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBasic), (void*) offsetof(VertexBasic, position));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBasic), (void*) offsetof(VertexBasic, color));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBasic), (void*) offsetof(VertexBasic, normal));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Logger::log(2, "%s: VAO and VBO initialized\n", __FUNCTION__);
}

void BasicVertexBuffer::cleanup() {
  glDeleteBuffers(1, &mVertexVBO);
  glDeleteVertexArrays(1, &mVAO);
}

void BasicVertexBuffer::uploadData(const std::vector<VertexBasic>& vertices) {
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexBasic), vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BasicVertexBuffer::bind() {
  glBindVertexArray(mVAO);
}

void BasicVertexBuffer::unbind() {
  glBindVertexArray(0);
}
