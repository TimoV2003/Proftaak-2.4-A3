#include <iostream>
#include <ostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
#include "colour_detection.h"
#include "GameService.h"
#include "tigl.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
std::unique_ptr<GameService> gameService;
std::thread visionThread;

void plagueRunInit();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW init failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    tigl::init();
    plagueRunInit();

    // TODO: possibly move this while loop to game service, 
    // Have rushed the coding so now its still here
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
        gameService->update();
        gameService->draw();
	}

    //TODO: send a signal to vision to close. then wait for it to stop.
    visionThread.join();

	glfwTerminate();
    return 0;
}


void plagueRunInit()
{
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    gameService = std::make_unique<GameService>(window);
    gameService->init();

    visionThread = std::thread(vision::color_detection_loop);
}