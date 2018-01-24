#include "Shader.h"

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
	printf("Shader::Shader\n");
	loader = new ShaderLoader;
	id = loader->loadShader(vertexFile, fragmentFile);
}

unsigned int Shader::get()
{
	return id;
}

void Shader::use() const
{
	glUseProgram(id);
}

void Shader::setInt(const std::string &name, const int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader()
{
	printf("Shader::~Shader\n");
	loader->deleteShader();
}
