#include "Object.h"

Object::Object(char *vertexFile, const char *fragmentFile, const char *textureFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 matAmbient, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess)
{
	printf("Object::Object\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;
	this->matAmbient = matAmbient;
	this->matDiffuse = matDiffuse;
	this->matSpecular = matSpecular;
	this->matShininess = shininess;

	shader = new Shader(vertexFile, fragmentFile);
	texture = new Texture(textureFile);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	vboFlag = TRUE;

	loadBuffers(vao, vbo, vertices);
}

Object::Object(char *vertexFile, const char *fragmentFile, const char *textureFile, GLenum drawType, unsigned int drawStart, unsigned int itemCount, std::vector<float> vertices, glm::vec3 matAmbient, glm::vec3 matDiffuse, glm::vec3 matSpecular, float shininess, unsigned int vbo)
{
	printf("Object::Object\n");

	this->drawType = drawType;
	this->drawStart = drawStart;
	this->itemCount = itemCount;
	this->matAmbient = matAmbient;
	this->matDiffuse = matDiffuse;
	this->matSpecular = matSpecular;
	this->matShininess = shininess;

	shader = new Shader(vertexFile, fragmentFile);
	texture = new Texture(textureFile);

	glGenVertexArrays(1, &vao);

	loadBuffers(vao, vbo, vertices);
}

void Object::loadBuffers(unsigned int vao, unsigned int vbo, std::vector<float> vertices)
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

GLuint Object::getVAO()
{
	return vao;
}

GLuint Object::getVBO()
{
	return vbo;
}

void Object::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 lightPos, glm::vec3 viewPos, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSecular, float lightConst, float lightLin, float lightQuad)
{
	texture->bind();
	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
	shader->setVec3("viewPos", viewPos);
	shader->setVec3("material.ambient", matAmbient);
	shader->setVec3("material.diffuse", matDiffuse);
	shader->setVec3("material.specular", matSpecular);
	shader->setFloat("material.shininess", matShininess);
	shader->setVec3("light.position", lightPos);
	shader->setVec3("light.ambient", lightAmbient);
	shader->setVec3("light.diffuse", lightDiffuse);
	shader->setVec3("light.specular", lightSecular);
	shader->setFloat("light.constant", lightConst);
	shader->setFloat("light.linear", lightLin);
	shader->setFloat("light.quadratic", lightQuad);

	glBindVertexArray(vao);
	glDrawArrays(drawType, drawStart, itemCount);
}

void Object::draw(glm::mat4 model)
{
	shader->use();
	shader->setMat4("model", model);

	glBindVertexArray(vao);
	glDrawArrays(drawType, drawStart, itemCount);
}

void Object::dontDisposeVBO()
{
	vboFlag = FALSE;
}

Object::~Object()
{
	printf("Object::~Object\n");
	glDeleteVertexArrays(1, &vao);
	if (vboFlag)
		glDeleteBuffers(1, &vbo);
	shader->~Shader();
	texture->~Texture();
}