#include "GameOver.h"
#include "..\tools\Logger.h"

void GameOver::init() {
    mVertexData.vertices.resize(4);

    /* front */
    mVertexData.vertices[0].position = glm::vec3(-0.5f, -0.4f, 0.5f);
    mVertexData.vertices[1].position = glm::vec3(0.5f, -0.4f, 0.5f);
    mVertexData.vertices[2].position = glm::vec3(0.5f, 0.4f, 0.5f);
    mVertexData.vertices[3].position = glm::vec3(-0.5f, 0.4f, 0.5f);

    mVertexData.vertices[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
    mVertexData.vertices[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
    mVertexData.vertices[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
    mVertexData.vertices[3].color = glm::vec3(1.0f, 1.0f, 1.0f);

    mVertexData.vertices[0].uv = glm::vec2(0.0, 0.0);
    mVertexData.vertices[1].uv = glm::vec2(1.0, 0.0);
    mVertexData.vertices[2].uv = glm::vec2(1.0, 1.0);
    mVertexData.vertices[3].uv = glm::vec2(0.0, 1.0);


    Logger::log(2, "%s: loaded %d vertices\n", __FUNCTION__, mVertexData.vertices.size());

    mVertexData.indices = std::initializer_list<unsigned int>{
        0, 1, 2, 2, 3, 0,       //front
    };
}

Mesh GameOver::getVertexData() {
    return mVertexData;
}
