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
#include <atomic>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
std::unique_ptr<GameService> gameService;
std::thread visionThread;
std::atomic<bool> visionShouldStop{ false };

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

        if (!gameService->gameOver) {
            gameService->update();
            gameService->draw();
            gameService->gameOverMessageShown = false;
        }
        else {
            if (!gameService->gameOverMessageShown) {
                std::cout << "Game Over!  Druk op R om opnieuw te starten." << std::endl;
                gameService->gameOverMessageShown = true;
            }
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                gameService->reset();
                gameService->gameOver = false;
                gameService->gameOverMessageShown = false;
            }
        }
    }
    //TODO: send a signal to vision to close. then wait for it to stop.

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

    visionThread = std::thread(vision::color_detection_loop, std::ref(visionShouldStop));
}