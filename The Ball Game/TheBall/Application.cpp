#include <GL\glew.h>
#include <GL\glfw.h>

#include <iostream>

#include "Application.h"
#include "Player.h"
#include "GPUProgram.h"
#include "Camera.h"
#include "Background.h"
//
#include "TestObject.h"

Application::Application()
	: screenHeight(768)
	, screenWidth(1366)
{
	player = new Player;
	camera = new Camera;
	obj = new TestObject;
	bg = new Background;
}

Application::~Application()
{
	delete player;
	delete camera;
	delete bg;
	//
	delete obj;
}

void Application::initializeScene()
{
	if (!glfwInit())
	{
		std::cerr << "Could not initialize GLFW\n";
	}

	// open a window with GLFW
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow(screenWidth, screenHeight, 8, 8, 8, 8, 32, 0, GLFW_WINDOW))
	{
		std::cerr << "glfwOpenWindow failed!\n";
	}

	// initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
	}

	while(glGetError() != GL_NO_ERROR) {}

	glEnable(GL_DEPTH);
	glShadeModel(GL_SMOOTH);

	player->prepareMaterial();
	//
	obj->prepareMaterial();

	/*camera->setCameraPosition(glm::vec3(0, 0, 0));
	camera->setViewportAspectRatio(screenWidth / screenHeight);*/
}

void Application::renderScene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player->drawPlayer();
	bg->drawBackground();
	//
	obj->drawObject();

	glfwSwapBuffers();
}

void Application::run()
{
	initializeScene();

	double lastTime = glfwGetTime();

	while (glfwGetWindowParam(GLFW_OPENED))
	{
		double thisTime = glfwGetTime();

		player->updatePosition(thisTime - lastTime);

		lastTime = thisTime;

		renderScene();
	}

	glfwTerminate();
}