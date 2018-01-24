#pragma once

#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
};

class Model
{
	Shader *shader;
	Texture *texture;
	int indicesCount = 0;
	unsigned int vbo;
	unsigned int vao;
	unsigned int ibo;

	void load(const char * objectFile);
public:
	Model(const char *vertexFile, const char *fragmentFile, const char *objectFile, const char *textureFile);
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	~Model();
};