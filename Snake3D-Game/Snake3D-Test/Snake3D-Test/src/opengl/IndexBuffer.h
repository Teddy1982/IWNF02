#pragma once

#include <memory>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer {
public:
	void init();
	void uploadData(const std::vector<unsigned int>& indices);
	void bind() const;
	void unbind() const;
	void draw(GLuint mode, unsigned int count);
	void cleanup();

	GLuint getCount() const;

private:
	GLuint mRendererID = 0;
	std::shared_ptr<std::vector<unsigned int>> mIndices;
};