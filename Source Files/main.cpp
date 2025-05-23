#include <iostream>
#include <ostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "CubeDrawComponent.h"
#include "tigl.h"
#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CubeDrawComponent.h"
#include "ModelLoader.h"
#include "MeshComponent.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

std::vector<std::shared_ptr<GameObject>> objects;

void init();
void update();
void draw();

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

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}


void init()
{
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    ///////// LE BIG INIT OF ENTITIES ////////
    auto blocky = std::make_shared<GameObject>("blocky");
    blocky->position = glm::vec3(0, 0, 0);
    blocky->addComponent(std::make_shared<CubeDrawComponent>(1.0f));
    blocky->addComponent(std::make_shared<GameComponent>());
    objects.push_back(blocky);

    Model treeModel;
    if (ModelLoader::load("Resource Files/Tree/Tree_1.obj", treeModel)) // Make sure this path is correct
    {
        auto tree = std::make_shared<GameObject>();
        tree->position = glm::vec3(2, 0, 0); // Move it to the right so you can see both
        tree->scale = glm::vec3(0.1f, 0.1f, 0.1f);
        tree->addComponent(std::make_shared<MeshComponent>(treeModel));
        objects.push_back(tree);
    }
    else
    {
        std::cerr << "Failed to load tree model!" << std::endl;
    }
}


void update()
{
    for (auto& object : objects) {
        object->update();
    }
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 modelMatrix(1);
    glm::mat4 viewMatrix(1);
    
    //GPT aspect ratio code. please make propper
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = width / (float)height;

    tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f));
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 5,10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    tigl::shader->setModelMatrix(modelMatrix);
    tigl::shader->enableColor(true);

    for (auto& object : objects) {
        object->draw();
    }
}