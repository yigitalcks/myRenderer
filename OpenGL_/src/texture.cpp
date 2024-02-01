#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "utility/stb_image.h"

Texture::Texture() : data{ nullptr }, width{ 0 }, height{ 0 }, nrChannels{ 0 } {

}
Texture::~Texture(){}

void Texture::load(const char* texturePath) {
	
	data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}