#include "Camera.h"
//#include "glm/gtx/string_cast.hpp"
//#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
	/*std::cout << "Position: " << glm::to_string(Position) << std::endl;
	std::cout << "Front: " << glm::to_string(Front) << std::endl;
	std::cout << "WorldUp: " << glm::to_string(WorldUp) << std::endl;*/
	position = pos;
	this->front = front;
	worldUp = up;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::KeyboardW(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position += front * velocity;
}

void Camera::KeyboardA(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position -= right * velocity;
}

void Camera::KeyboardS(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position -= front * velocity;
}

void Camera::KeyboardD(float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	position += right * velocity;
}

void Camera::MouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateCameraVectors();
}

