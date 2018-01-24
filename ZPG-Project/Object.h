#pragma once

#include "Shader.h"
#include "Texture.h"
#include <vector>

class Object
{
	unsigned int vbo;
	unsigned int vao;
	GLenum drawType;
	unsigned int drawStart;
	unsigned int itemCount;
	glm::vec3 matAmbient;
	glm::vec3 matDiffuse;
	glm::vec3 matSpecular;
	float matShininess;
	bool vboFlag = FALSE;

	void loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices);

public:
	Shader* shader;
	Texture* texture;
	Object(char *vertexFile, const char *fragmentFile, const char *textureFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 matAmbient, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess);
	Object(char *vertexFile, const char *fragmentFile, const char *textureFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 matAmbient, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess, unsigned int vbo);
	unsigned int getVAO();
	unsigned int getVBO();
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 lightPos, glm::vec3 viewPos, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSecular, float lightConst, float lightLin, float lightQuad);
	void draw(glm::mat4 model);
	void dontDisposeVBO();
	~Object();
};