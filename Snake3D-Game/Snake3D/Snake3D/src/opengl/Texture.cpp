#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include "..\tools\Logger.h"

void Texture::cleanup() {
  glDeleteTextures(1, &mTexture);
}

bool Texture::loadTexture(std::string textureFilename) {
  mTextureName = textureFilename;

  stbi_set_flip_vertically_on_load(true);
  unsigned char *textureData = stbi_load(textureFilename.c_str(), &mTexWidth, &mTexHeight, &mNumberOfChannels, STBI_rgb_alpha);

  if (!textureData) {
    Logger::log(2, "%s error: could not load file '%s'\n", __FUNCTION__, mTextureName.c_str());
    return false;
  }

  glGenTextures(1, &mTexture);
  glBindTexture(GL_TEXTURE_2D, mTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTexWidth, mTexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(textureData);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  Logger::log(2, "%s: texture '%s' loaded (%dx%d, %d channels)\n", __FUNCTION__, mTextureName.c_str(), mTexWidth, mTexHeight, mNumberOfChannels);
  return true;
}

void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, mTexture);
}

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
