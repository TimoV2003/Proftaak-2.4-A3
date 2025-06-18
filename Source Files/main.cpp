#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STB_TRUETYPE_IMPLEMENTATION 

#include <iostream>
#include <ostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "TextRenderer.h"

#ifdef _DEBUG
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

#include <thread>
#include "colour_detection.h"
#include "GameService.h"
#include "tigl.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

enum class GameState{ Playing,GameOver };
GameState currentState = GameState::Playing;

GLFWwindow* window;
std::unique_ptr<GameService> gameService;
std::thread visionThread;
std::atomic<bool> visionShouldStop{ false };
TextRenderer textRenderer;


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
	
    //disable V-sync = 0, enable V-sync = 1
    glfwSwapInterval(0);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW init failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    plagueRunInit();
    tigl::init();

#ifdef _DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);
#endif

    // TODO: possibly move this while loop to game service, 
    // Have rushed the coding so now its still here
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        switch (currentState)
        {
        case GameState::Playing:
            gameService->update();
            gameService->draw();
            textRenderer.writeText("Hello World", "times", glm::vec4(100, 0, 0, 1));
#ifdef _DEBUG
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            gameService->imgGuiUpdate();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
            gameService->gameOverMessageShown = false;
            if (gameService->gameOver) {
                currentState = GameState::GameOver;
            }
            break;

        case GameState::GameOver:
            if (!gameService->gameOverMessageShown) {
                std::cout << "Game Over! Press R to restart." << std::endl;
                gameService->gameOverMessageShown = true;
            }
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                gameService->reset();
                gameService->gameOver = false;
                gameService->gameOverMessageShown = false;
                currentState = GameState::Playing;
            }
            break;
        }
    }
	visionShouldStop = true;
	if (visionThread.joinable())
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

	textRenderer.loadFont("times", "c:/windows/fonts/times.ttf");

    gameService = std::make_unique<GameService>(window);
    gameService->init();

    //visionThread = std::thread(vision::color_detection_loop, std::ref(visionShouldStop));
}