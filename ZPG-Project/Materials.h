#pragma once
#include <glm/glm.hpp>

struct LightValues {
	glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};

struct WoodTexture {
	string file = ".\\texture\\woodBox.jpg";
	glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.0f);
	glm::vec3 diffuse = glm::vec3(0.05f, 0.05f, 0.0f);
	glm::vec3 specular = glm::vec3(0.1f, 0.1f, 0.1f);
	float shininess = 2.0f;
};

struct SteelTexture {
	string file = ".\\texture\\aluminium-brushed-metal-texture.jpg";
	glm::vec3 ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
	glm::vec3 diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
	glm::vec3 specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
	float shininess = 51.2f;
};

struct LightValues lightVal;
struct WoodTexture woodTex;
struct SteelTexture steelTex;