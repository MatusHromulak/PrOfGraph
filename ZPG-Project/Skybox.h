#pragma once
#include "Shader.h"
#include "Texture.h"
#include <vector>

class Skybox
{
	unsigned int vbo;
	unsigned int vao;
	unsigned int texId;
	GLenum drawType;
	unsigned int drawStart;
	unsigned int itemCount;
	bool vboFlag = FALSE;

	void loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices);
	void loadCubemap(vector<std::string> faces);

public:
	Shader* shader;
	Skybox(char *vertexFile, const char *fragmentFile, vector<std::string> faces, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices);
	Skybox(char *vertexFile, const char *fragmentFile, vector<std::string> faces, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, unsigned int vbo);
	unsigned int getVAO();
	unsigned int getVBO();
	void draw(glm::mat4 projection, glm::mat4 view);
	void dontDisposeVBO();
	~Skybox();
};