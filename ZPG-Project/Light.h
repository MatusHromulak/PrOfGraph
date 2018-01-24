#pragma once

#include "Shader.h"
#include "Texture.h"

#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
	unsigned int vbo;
	unsigned int vao;
	GLenum drawType;
	unsigned int drawStart;
	unsigned int itemCount;
	glm::vec3 position;
	float scale;
	glm::mat4 model;
	bool vboFlag = FALSE;

	void loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices);

public:
	Shader* shader;
	Light(char *vertexFile, const char *fragmentFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 position, float scale);
	Light(char *vertexFile, const char *fragmentFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 position, float scale, unsigned int vbo);
	unsigned int getVAO();
	unsigned int getVBO();
	glm::vec3 GetPosition();
	void draw(glm::mat4 projection, glm::mat4 view);
	void draw(glm::mat4 model);
	void dontDisposeVBO();
	~Light();
};