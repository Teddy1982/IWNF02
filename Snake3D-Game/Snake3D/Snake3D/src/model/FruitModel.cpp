#include "FruitModel.h"
#include "..\tools\Logger.h"

void FruitModel::init(int xpos, int ypos, int zpos) {
	mVertexData.vertices.resize(24);

	/* front */
	mVertexData.vertices[0].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[1].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[2].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[3].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);

	mVertexData.vertices[0].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[2].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[3].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[0].normal = glm::vec3(0.0f, 0.0f, -1.0f);
	mVertexData.vertices[1].normal = glm::vec3(0.0f, 0.0f, -1.0f);
	mVertexData.vertices[2].normal = glm::vec3(0.0f, 0.0f, -1.0f);
	mVertexData.vertices[3].normal = glm::vec3(0.0f, 0.0f, -1.0f);

	/* back */
	mVertexData.vertices[4].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[5].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[6].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[7].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);

	mVertexData.vertices[4].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[5].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[6].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[7].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[4].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	mVertexData.vertices[5].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	mVertexData.vertices[6].normal = glm::vec3(0.0f, 0.0f, 1.0f);
	mVertexData.vertices[7].normal = glm::vec3(0.0f, 0.0f, 1.0f);

	/* left */
	mVertexData.vertices[8].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[9].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[10].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[11].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);

	mVertexData.vertices[8].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[9].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[10].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[11].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[8].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	mVertexData.vertices[9].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	mVertexData.vertices[10].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	mVertexData.vertices[11].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

	/* right */
	mVertexData.vertices[12].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[13].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[14].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[15].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);

	mVertexData.vertices[12].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[13].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[14].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[15].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[12].normal = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[13].normal = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[14].normal = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[15].normal = glm::vec3(1.0f, 0.0f, 0.0f);

	/* top */
	mVertexData.vertices[16].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[17].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[18].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[19].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.4f + (ypos * 0.1f) - 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);

	mVertexData.vertices[16].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[17].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[18].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[19].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[16].normal = glm::vec3(0.0f, 1.0f, 0.0f);
	mVertexData.vertices[17].normal = glm::vec3(0.0f, 1.0f, 0.0f);
	mVertexData.vertices[18].normal = glm::vec3(0.0f, 1.0f, 0.0f);
	mVertexData.vertices[19].normal = glm::vec3(0.0f, 1.0f, 0.0f);

	/* bottom */
	mVertexData.vertices[20].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[21].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.4f + (zpos * 0.1f) - 0.001f);
	mVertexData.vertices[22].position = glm::vec3(-0.5f + (xpos * 0.1f) + 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);
	mVertexData.vertices[23].position = glm::vec3(-0.4f + (xpos * 0.1f) - 0.001f, -0.5f + (ypos * 0.1f) + 0.001f, -0.5f + (zpos * 0.1f) + 0.001f);

	mVertexData.vertices[20].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[21].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[22].color = glm::vec3(1.0f, 0.0f, 0.0f);
	mVertexData.vertices[23].color = glm::vec3(1.0f, 0.0f, 0.0f);

	mVertexData.vertices[20].normal = glm::vec3(0.0f, -1.0f, 0.0f);
	mVertexData.vertices[21].normal = glm::vec3(0.0f, -1.0f, 0.0f);
	mVertexData.vertices[22].normal = glm::vec3(0.0f, -1.0f, 0.0f);
	mVertexData.vertices[23].normal = glm::vec3(0.0f, -1.0f, 0.0f);

	Logger::log(2, "%s: loaded %d vertices\n", __FUNCTION__, mVertexData.vertices.size());

	mVertexData.indices = std::initializer_list<unsigned int>{
		0, 1, 3, 3, 1, 2,	//front
		4, 5, 7, 7, 5, 6,	//back
		8, 9, 11, 11, 9, 10,	//left		
		12, 13, 15, 15, 13, 14,	// right
		16, 17, 19, 19, 17, 18,	// top
		20, 21, 23, 23, 21, 22	// bottom
	};
}

MeshBasic FruitModel::getVertexData() {
	return mVertexData;
}