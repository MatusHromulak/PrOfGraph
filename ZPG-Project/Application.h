#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

class Application
{
	GLFWwindow* window;
	static Application *inst;

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	bool firstMouse = true;
	float lastX;
	float lastY;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	Application();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);

public:
	static Application* getInstance();
	bool init(int argc, char* argv[]);
	void callBackFunctions();
	void run();
	~Application();
};