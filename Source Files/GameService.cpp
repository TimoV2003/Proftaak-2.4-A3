#include "GameService.h"
#include <iostream>
#include "GameObject.h"
#include "ModelLoader.h"
#include "MeshComponent.h"
#include "PlayerComponent.h"
#include "KeyboardInput.h"
#include "I_InputStrategy.h"
#include "tigl.h"
using tigl::Vertex;

double lastFrameTime = 0;
std::vector<std::shared_ptr<GameObject>> objects;
std::shared_ptr<IInputStrategy> keyboardInput;

void GameService::init() 
{
    keyboardInput = std::make_shared<KeyboardInput>();

    //game object creation
    Model treeModel;
    if (ModelLoader::load("Resource Files/Tree/Tree_2.obj", treeModel)) // Make sure this path is correct
    {
        auto blocky = std::make_shared<GameObject>("blocky");
        blocky->position = glm::vec3(0, 0, 0);
        blocky->scale = glm::vec3(0.2f, 0.2f, 0.2f);
        blocky->addComponent(std::make_shared<PlayerComponent>(keyboardInput));
        blocky->addComponent(std::make_shared<MeshComponent>(treeModel));
        objects.push_back(blocky);
    }
    else
    {
        std::cerr << "Failed to load tree model!" << std::endl;
    }

    Model treeModel2;
    if (ModelLoader::load("Resource Files/Tree/Tree_1.obj", treeModel2)) // Make sure this path is correct
    {
        auto tree = std::make_shared<GameObject>("tree");
        tree->position = glm::vec3(5, 0, 0); // Move it to the right so you can see both
        tree->scale = glm::vec3(0.1f, 0.1f, 0.1f);
        tree->addComponent(std::make_shared<MeshComponent>(treeModel2));
        objects.push_back(tree);
    }
    else
    {
        std::cerr << "Failed to load tree model!" << std::endl;
    }
}

void GameService::update()
{
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    for (auto& object : objects) {
        object->update((float)deltaTime);
    }
}

void GameService::draw()
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
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    tigl::shader->setModelMatrix(modelMatrix);
    tigl::shader->enableColor(true);

    for (auto& object : objects) {
        object->draw();
    }
}

