#include "Application.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
	Application *app;
	app = app->getInstance();

	if (!app->init(argc, argv)) {
		exit(EXIT_FAILURE);
	}
	app->callBackFunctions();
	app->run();
	return 0;
}
