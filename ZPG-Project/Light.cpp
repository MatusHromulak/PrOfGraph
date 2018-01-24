#include "Light.h"


Light::Light(char *vertexFile, const char *fragmentFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 position, float scale)
{
	printf("Light::Light\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;
	this->position = position;
	this->scale = scale;
	
	shader = new Shader(vertexFile, fragmentFile);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	vboFlag = TRUE;

	loadBuffers(vao, vbo, vertices);

	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(scale));
}

Light::Light(char *vertexFile, const char *fragmentFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 position, float scale, unsigned int vbo)
{
	printf("Light::Light\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;
	this->position = position;

	shader = new Shader(vertexFile, fragmentFile);

	glGenVertexArrays(1, &vao);

	loadBuffers(vao, vbo, vertices);

	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(scale));
}

void Light::loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices)
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

GLuint Light::getVAO()
{
	return vao;
}

GLuint Light::getVBO()
{
	return vbo;
}

glm::vec3 Light::GetPosition()
{
	return position;
}

void Light::draw(glm::mat4 projection, glm::mat4 view)
{
	shader->use();
	
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);

	glBindVertexArray(vao);
	glDrawArrays(drawType, drawStart, itemCount);
}

void Light::draw(glm::mat4 model)
{
	shader->setMat4("model", model);

	glBindVertexArray(vao);
	glDrawArrays(drawType, drawStart, itemCount);
}

void Light::dontDisposeVBO()
{
	vboFlag = FALSE;
}

Light::~Light()
{
	printf("Light::~Light\n");
	glDeleteVertexArrays(1, &vao);
	if (vboFlag)
		glDeleteBuffers(1, &vbo);
	shader->~Shader();
}