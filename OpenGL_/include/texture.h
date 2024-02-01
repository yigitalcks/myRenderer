#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <iostream>

class Texture {
public:
	Texture();
	~Texture();

	void load(const char* texturePath);

private:
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
};


#endif

