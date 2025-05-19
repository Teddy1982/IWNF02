#include "IndexBuffer.h"

void IndexBuffer::init() {
    glGenBuffers(1, &mRendererID);
}

void IndexBuffer::cleanup() {
    glDeleteBuffers(1, &mRendererID);
}

void IndexBuffer::uploadData(const std::vector<unsigned int>& indices) {
    mIndices = std::make_shared<std::vector<unsigned int>>(indices);

    if (mRendererID == 0) {
        glGenBuffers(1, &mRendererID);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices->size() * sizeof(unsigned int), mIndices->data(), GL_DYNAMIC_DRAW);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mIndices->clear();
}

void IndexBuffer::draw(GLuint mode, unsigned int count) {
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
}

GLuint IndexBuffer::getCount() const {
	return mIndices->size();
}
