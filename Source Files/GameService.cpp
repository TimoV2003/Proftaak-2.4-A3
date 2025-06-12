#include "GameService.h"
#include <iostream>

#include "GameObject.h"
#include "ModelLoader.h"
#include "MeshComponent.h"
#include "PlayerComponent.h"
#include "KeyboardInput.h"
#include "VisionInput.h"
#include "EnemyComponent.h"
#include "I_InputStrategy.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "I_ScoreStrategy.h"
#include "ScoreHolder.h"
#include "UiScoreComponent.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "tigl.h"

using tigl::Vertex;

//TESTING please delete when ready
#include "TestSpawnerComponent.h"
#include <ScoreComponent.h>

static bool showingDebugMenu = true;
static double lastFrameTime = 0;
std::vector<std::shared_ptr<GameObject>> objects;
std::vector<std::shared_ptr<GameObject>> pendingAdding;
std::vector<std::shared_ptr<GameObject>> pendingDeletion;
std::shared_ptr<IInputStrategy> keyboardInput;
std::shared_ptr<IInputStrategy> visionInput;
std::shared_ptr<IScoreStrategy> scoreHolder;

void imgGuiUpdate();

void GameService::init() 
{
    keyboardInput = std::make_shared<KeyboardInput>();
    visionInput = std::make_shared<VisionInput>();
    scoreHolder = std::make_shared<ScoreHolder>();

    /////  GAME OBJECT CREATION  /////
    Model treeModel;
    if (ModelLoader::load("Resource Files/Tree/Tree_1.obj", treeModel)) // Make sure this path is correct
    {
        auto blocky = std::make_shared<GameObject>("blocky");
        blocky->position = glm::vec3(0, 0, 0);
        blocky->scale = glm::vec3(0.2f, 0.2f, 0.2f);
        blocky->addComponent(std::make_shared<PlayerComponent>(keyboardInput));
        blocky->addComponent(std::make_shared<MeshComponent>(treeModel));
        auto health = std::make_shared<HealthComponent>(5,1.0f);
        blocky->addComponent(health);
        blocky->addComponent(std::make_shared<DistanceScoreComponent>(scoreHolder));
        instantiate(blocky);

        auto uiObject = std::make_shared<GameObject>("uiObject");
        uiObject->addComponent(std::make_shared<UiScoreComponent>(scoreHolder));
        instantiate(uiObject);
    

        //test spawner. feel free to delete in entirity
        auto testSpawner = std::make_shared<GameObject>("testSpawner");
        testSpawner->addComponent(std::make_shared<TestSpawnerComponent>(treeModel));
        instantiate(testSpawner);
    }
    else
    {
        std::cerr << "Failed to load tree model!" << std::endl;
    }

    objects.insert(objects.end(), pendingAdding.begin(), pendingAdding.end());
}

void GameService::update()
{
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    for (auto& object : objects) {
        object->update((float)deltaTime);
    }

    //add new objects
    if (!pendingAdding.empty())
    {
        objects.insert(objects.end(), pendingAdding.begin(), pendingAdding.end());
        pendingAdding.clear();
    }

    //remove requested objects
    if (!pendingDeletion.empty()) {
        for (auto& toDelete : pendingDeletion) {
            objects.erase(std::remove(objects.begin(), objects.end(), toDelete), objects.end());
        }
        pendingDeletion.clear();
    }

    imgGuiUpdate();
}

void GameService::draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glm::mat4 modelMatrix(1);
    glm::mat4 viewMatrix(1);

    //GPT aspect ratio code. please make propper
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = width / (float)height;

    tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f));
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    tigl::shader->setModelMatrix(modelMatrix);
    tigl::shader->enableColor(false);

    for (auto& object : objects) {
        object->draw();
    }
}

void imgGuiUpdate()
{
    if (showingDebugMenu) {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0));
        ImGui::SetNextWindowSize(ImVec2(200, 0));
        ImGui::Begin("DebugMenu", &showingDebugMenu);

        ImGui::Text("distance score: %.1f", scoreHolder->getDistanceScore());
        ImGui::Text("potion score: %.1f", scoreHolder->getPotionScore());
        ImGui::Text("framerate: %.1f FPS", ImGui::GetIO().Framerate);

        ImGui::End();
    }
}

void GameService::instantiate(std::shared_ptr<GameObject> object)
{
    //TODO add nullptr check, should to this to a lot of functions
    object->setGameService(this);
    pendingAdding.push_back(object);
}

//TODO not tested, but should work
std::shared_ptr<GameObject> GameService::getGameObject(std::string tag)
{
    for (auto& object : objects)
    {
        if (tag == object->getTag()) return object;
    }
    return nullptr;
}

void GameService::queueDelete(std::shared_ptr<GameObject>& object)
{
    // find = return index of first find or index of end (last index + 1)
    // so if find == vector.end() then nothing was found
    if (std::find(pendingDeletion.begin(), pendingDeletion.end(), object) == pendingDeletion.end()) {
        pendingDeletion.push_back(object);
    }
}





