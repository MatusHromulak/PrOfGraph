#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Camera
{
	glm::vec3 position;// = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 front;// = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;// = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = -90.0f;
	float pitch = 0.0f;
	float movementSpeed = 10.0f;
	float mouseSensitivity = 0.1f;

	void updateCameraVectors();

public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
	glm::mat4 GetViewMatrix();
	glm::vec3 GetPosition();
	void KeyboardW(float deltaTime);
	void KeyboardA(float deltaTime);
	void KeyboardS(float deltaTime);
	void KeyboardD(float deltaTime);
	void MouseMovement(float xoffset, float yoffset);
};