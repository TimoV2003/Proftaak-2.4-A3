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
#include "ColourDetection.h"
#include "GameService.h"
#include "tigl.h"
#include "StartMenu.hpp"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

enum class GameState{ Playing,GameOver, StartMenu, Loading };
GameState currentState = GameState::StartMenu;

GLFWwindow* window;
std::unique_ptr<GameService> gameService;
TextRenderer textRendererr;
std::thread visionThread;

std::atomic<bool> visionShouldStop{ false };

void plagueRunInit();
void onStartMenuButtonPressed();

StartMenu* startMenu;

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Plague Run", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

	// set callback for window resize
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    //disable V-sync = 0, enable V-sync = 1
    glfwSwapInterval(0);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW init failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    //plagueRunInit();
    textRendererr.initFont("times", "c:/windows/fonts/times.ttf");
    textRendererr.setActiveFont("times");
    textRendererr.setActiveColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    startMenu = new StartMenu(window);
    startMenu->init();
	startMenu->setCallbackOnButtonPress([=]() {
		std::cout << "Button Pressed!" << std::endl;
		currentState = GameState::Loading;
		});
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
        glfwPollEvents();
        glfwSwapBuffers(window);

        switch (currentState)
        {
        case GameState::StartMenu: {
			startMenu->update();
			startMenu->draw();
            glfwSwapBuffers(window);
            startMenu->draw();
            break;
        }
        case GameState::Loading: {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
            gameService->init();
            glfwSwapBuffers(window);
            currentState = GameState::Playing;
            break;
        }
        case GameState::Playing:
            gameService->update();
            gameService->draw();
#ifdef _DEBUG
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            gameService->imgGuiUpdate();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
            if (gameService->gameOver) {
                currentState = GameState::GameOver;
            }
            break;

        case GameState::GameOver:
			// continue drawing the game but not updating
            gameService->draw();
#ifdef _DEBUG 
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            gameService->imgGuiUpdate();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif 
            gameService->reset();
            gameService->gameOver = false;
            currentState = GameState::StartMenu;
            break;
        }
    }
	visionShouldStop = true;
	if (visionThread.joinable())
		visionThread.join(); 

    glfwTerminate();
    delete startMenu;
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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	startMenu->setWindowSize(static_cast<float>(width/2.0f), static_cast<float>(height/2.0f));


    gameService = std::make_unique<GameService>(window);

    visionThread = std::thread(vision::color_detection_loop, std::ref(visionShouldStop));
}

void onStartMenuButtonPressed() {
    std::cout << "Button Pressed!" << std::endl;
    currentState = GameState::Loading;
}