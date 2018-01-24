#include "Application.h"
#include "Cube.h"
#include "SkyboxData.h"
#include "Object.h"
#include "Light.h"
#include "Skybox.h"
#include "Materials.h"
#include "Shader.h"
#include "Model.h"

Application::Application()
{
	printf("Application\n");
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->KeyboardW(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->KeyboardA(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->KeyboardD(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->KeyboardS(deltaTime);
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("Application::window_size_callback\n");
	glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);

	if (firstMouse)
	{
		lastX = (float)mouseX;
		lastY = (float)mouseY;
		firstMouse = false;
	}
	
	float xoffset = (float)mouseX - lastX;
	float yoffset = lastY - (float)mouseY;

	//printf("offset %f, %f \n", xoffset, yoffset);

	lastX = (float)mouseX;
	lastY = (float)mouseY;

	camera->MouseMovement(xoffset, yoffset);
}

Application* Application::inst = NULL;

Application* Application::getInstance()
{
	if (inst == NULL)
	{
		inst = new Application();
		return inst;
	}
	else
		return inst;
}

bool Application::init(int argc, char* argv[])
{
	printf("Application::init\n");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "ZPG", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW window error" << std::endl;
		glfwTerminate();
		return FALSE;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD error" << std::endl;
		return FALSE;
	}

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return TRUE;
}

void Application::callBackFunctions()
{
	printf("Application::callBackFunctions\n");
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });
}

void Application::run()
{
	printf("Application::run\n");

	Object woodCube(".\\shader\\CubeVS.glsl", ".\\shader\\CubeFS.glsl", woodTex.file.c_str(), GL_TRIANGLES, 0, cubeItemCount, cubeVertices, woodTex.ambient, woodTex.diffuse, woodTex.specular, woodTex.shininess);
	unsigned int vbo = woodCube.getVBO();
	woodCube.dontDisposeVBO();
	
	Object steelCube(".\\shader\\CubeVS.glsl", ".\\shader\\CubeFS.glsl", steelTex.file.c_str(), GL_TRIANGLES, 0, cubeItemCount, cubeVertices, steelTex.ambient, steelTex.diffuse, steelTex.specular, steelTex.shininess, vbo);
	Light cubeSun(".\\shader\\LightVS.glsl", ".\\shader\\LightFS.glsl", GL_TRIANGLES, 0, cubeItemCount, cubeVertices, glm::vec3(1.0f, 1.0f, 0.0f), 0.1f, vbo);
	Skybox skybox(".\\shader\\SkyboxVS.glsl", ".\\shader\\SkyboxFS.glsl", faces, GL_TRIANGLES, 0, skyboxItemCount, skyboxVertices);
	Model testModel(".\\shader\\ModelVS.glsl", ".\\shader\\ModelFS.glsl", ".\\object\\test\\test.obj", ".\\object\\test\\test.png");
	//Model testModel(".\\shader\\ModelVS.glsl", ".\\shader\\ModelFS.glsl", ".\\object\\rabbit\\Rabbit.obj", ".\\object\\rabbit\\Rabbit_D.tga");

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 model;

		model = glm::translate(model, glm::vec3(1.0f, -0.84f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f));
		testModel.draw(projection, view, model);

		model = glm::mat4();
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 1.0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
		woodCube.draw(projection, view, model, cubeSun.GetPosition(), camera->GetPosition(), lightVal.ambient, lightVal.diffuse, lightVal.specular, lightVal.constant, lightVal.linear, lightVal.quadratic);
		
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 1.0));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(-1.0f, -1.0f, -1.0f));
		woodCube.draw(model);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -0.86f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 0.01f, 20.0f));
		steelCube.draw(projection, view, model, cubeSun.GetPosition(), camera->GetPosition(), lightVal.ambient, lightVal.diffuse, lightVal.specular, lightVal.constant, lightVal.linear, lightVal.quadratic);
		
		cubeSun.draw(projection, view);

		view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
		skybox.draw(projection, view);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vbo);

	glfwDestroyWindow(window);
	glfwTerminate();
}

Application::~Application()
{
	printf("~Application\n");
}