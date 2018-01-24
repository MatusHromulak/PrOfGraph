#pragma once

#include "glad\glad.h"
#include "stb_image.h"

#include <iostream>

class Texture
{
	unsigned int id;
public:
	Texture(const char *textureFile);
	unsigned int get();
	void bind();
	~Texture();
};