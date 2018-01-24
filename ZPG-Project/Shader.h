#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderLoader.h"

class Shader
{
	unsigned int id;
	ShaderLoader* loader;
public:
	Shader(const char *vertexFile, const char *fragmentFile);
	unsigned int get();
	void use() const;
	void setInt(const std::string &name, const int value) const;
	void setFloat(const std::string &name, const float value) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	~Shader();
};