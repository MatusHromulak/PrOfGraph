#include "Texture.h"

Texture::Texture(const char *textureFile)
{
	printf("Texture::Texture %s\n", textureFile);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, nrChannels;

	unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Texture load fail" << std::endl;
	}

	stbi_image_free(data);
}

unsigned int Texture::get()
{
	return id;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture()
{
	printf("Texture::~Texture\n");
	if (id != 0)
	{
		glDeleteTextures(1, &id);
		id = 0;
	}
}