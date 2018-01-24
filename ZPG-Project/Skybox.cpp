#include "Skybox.h"

Skybox::Skybox(char * vertexFile, const char * fragmentFile, vector<std::string> faces, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices)
{
	printf("Skybox::Skybox\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;

	shader = new Shader(vertexFile, fragmentFile);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	vboFlag = TRUE;

	loadBuffers(vao, vbo, vertices);

	loadCubemap(faces);
}

Skybox::Skybox(char *vertexFile, const char *fragmentFile, vector<std::string> faces, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, unsigned int vbo)
{
	printf("Skybox::Skybox\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;

	shader = new Shader(vertexFile, fragmentFile);

	glGenVertexArrays(1, &vao);

	loadBuffers(vao, vbo, vertices);

	loadCubemap(faces);
}

void Skybox::loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Skybox::loadCubemap(vector<std::string> faces)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

unsigned int Skybox::getVAO()
{
	return vao;
}

unsigned int Skybox::getVBO()
{
	return vbo;
}

void Skybox::draw(glm::mat4 projection, glm::mat4 view)
{
	glDepthFunc(GL_LEQUAL);
	shader->use();
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
	glDrawArrays(drawType, drawStart, itemCount);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void Skybox::dontDisposeVBO()
{
	vboFlag = FALSE;
}

Skybox::~Skybox()
{
	printf("Skybox::~Skybox\n");
	glDeleteVertexArrays(1, &vao);
	if (vboFlag)
		glDeleteBuffers(1, &vbo);
	shader->~Shader();
}
