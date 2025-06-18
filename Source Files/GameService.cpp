#include "GameService.h"
#include <iostream>
#include <mutex>
#include "tigl.h"
#ifdef _DEBUG
#include "DebugReferenceCounter.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif
#include "GameObject.h"
#include "ModelLoader.h"
#include "tigl.h"
#include "ScoreStrategy.h"
#include "colour_detection.h"
#include "MatToTexHelper.h" 

//this include section is needed for the components
#include "SpawnerComponent.h"
#include "MeshComponent.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "distanceScoreComponent.h"
#include "TreadmillComponent.h"

// this include section is needed for the input strategy
#include "../patterns/strategy/interfaces/I_InputStrategy.h"
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"
#include "../patterns/strategy/input_strategies/Headers/KeyboardInput.h"
#include "../patterns/strategy/input_strategies/Headers/VisionInput.h"
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

using tigl::Vertex;

static bool showingDebugMenu = true;
static double lastFrameTime = 0;
static double deltaTime = 0.0f;

std::vector<std::shared_ptr<GameObject>> objects;
std::vector<std::shared_ptr<GameObject>> pendingAdding;
std::vector<std::shared_ptr<GameObject>> pendingDeletion;
std::shared_ptr<IInputStrategy> keyboardInput;
std::shared_ptr<IInputStrategy> visionInput;
std::shared_ptr<IEndOfMillBehavior> floormillBehavior;
std::shared_ptr<ScoreStrategy> distanceScoreHolder;
std::shared_ptr<ScoreStrategy> potionScoreHolder;

void GameService::init()
{
    keyboardInput = std::make_shared<KeyboardInput>();
    visionInput = std::make_shared<VisionInput>();
	distanceScoreHolder = std::make_shared<ScoreStrategy>();
	potionScoreHolder = std::make_shared<ScoreStrategy>();
	floormillBehavior = std::make_shared<FloorMillBehavior>();

    /////  GAME OBJECT CREATION  /////
    Model PlayerModel;
    if (ModelLoader::load("Resource Files/PlayerModel/PlayerPlauge.obj", PlayerModel)) // Make sure this path is correct
    {
        auto blocky = std::make_shared<GameObject>("blocky",2);
        blocky->position = glm::vec3(0, 0, 6);
        blocky->scale = glm::vec3(0.7f, 0.7f, 0.7f);
        blocky->addComponent(std::make_shared<PlayerComponent>(visionInput));
        blocky->addComponent(std::make_shared<MeshComponent>(PlayerModel));
		auto health = std::make_shared<HealthComponent>(5, 1.0f); 
		blocky->addComponent(health);
        blocky->addComponent(std::make_shared<HealthComponent>(5, 1.0f));
		blocky->addComponent(std::make_shared<DistanceScoreComponent>(distanceScoreHolder));
        instantiate(blocky);

    }
    //TODO make this debug
    /*else
    {
        std::cerr << "Failed to load tree model!" << std::endl;
    }*/
    
    Model GroundPlane;
    if (ModelLoader::load("Resource Files/GroundPlane/GroundTile.obj", GroundPlane)) // Make sure this path is correct
    {
        for (size_t i = 0; i < 9; i++)
        {
            auto ground = std::make_shared<GameObject>("ground", 1);
            ground->position = glm::vec3(0, -1, 25.0f + (i * -50.0f));
            ground->scale = glm::vec3(10.0f, 1.0f, 10.0f);
            ground->addComponent(std::make_shared<MeshComponent>(GroundPlane));
            ground->addComponent(std::make_shared<TreadmillComponent>(floormillBehavior));
            instantiate(ground);
        }
        
    }

    Model LeftHouse1;
    if (ModelLoader::load("Resource Files/House/House1.obj", LeftHouse1)) // Make sure this path is correct
    {
        for (size_t i = 0; i < 20; i++)
        {
            auto house = std::make_shared<GameObject>("house", 1);
            house->position = glm::vec3(-21, -1, 15.0f + (i * -15.0f));
            house->scale = glm::vec3(3.0f, 3.0f, 3.0f);
            house->rotation = glm::vec3(0.0f, 1.57f, 0.0f);
            house->addComponent(std::make_shared<MeshComponent>(LeftHouse1));
            house->addComponent(std::make_shared<TreadmillComponent>(floormillBehavior));
            instantiate(house);
        }
            
    }
    Model RightHouse1;
    if (ModelLoader::load("Resource Files/House/House1.obj", RightHouse1)) // Make sure this path is correct
    {
        for (size_t i = 0; i < 20; i++)
        {
            auto house = std::make_shared<GameObject>("house", 1);
            house->position = glm::vec3(21, -1, 15.0f + (i * -15.0f));
            house->scale = glm::vec3(3.0f, 3.0f, 3.0f);
            house->rotation = glm::vec3(0.0f, -1.57f, 0.0f);
            house->addComponent(std::make_shared<MeshComponent>(RightHouse1));
            house->addComponent(std::make_shared<TreadmillComponent>(floormillBehavior));
            instantiate(house);
        }

    }
    auto testSpawner = std::make_shared<GameObject>("testSpawner");
    float Spawnerdistance = -50.0f;
    testSpawner->position = glm::vec3(0, 0, Spawnerdistance);
    testSpawner->addComponent(std::make_shared<SpawnerComponent>(1.0f, 5.0f));
    instantiate(testSpawner);

    objects.insert(objects.end(), pendingAdding.begin(), pendingAdding.end());
	pendingAdding.clear();
}

void GameService::update()
{
    double currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
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

void GameService::reset() {
	objects.clear();
	pendingAdding.clear();
	pendingDeletion.clear();
    init();
	gameOverMessageShown = false;
    }

void GameService::queueDelete(std::shared_ptr<GameObject>& object)
{
    // find = return index of first find or index of end (last index + 1)
    // so if find == vector.end() then nothing was found
    if (std::find(pendingDeletion.begin(), pendingDeletion.end(), object) == pendingDeletion.end()) {
        pendingDeletion.push_back(object);
    }
}

#ifdef _DEBUG
void GameService::imgGuiUpdate()
{
    static int lastKeyCode = -1;
    int keyPressed = glfwGetKey(window, GLFW_KEY_F1);
    if (keyPressed == GLFW_PRESS && keyPressed != lastKeyCode) {
        showingDebugMenu = !showingDebugMenu;
    }
    lastKeyCode = keyPressed;

    int imGuiWindowSize = 300;
    if (showingDebugMenu) {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - imGuiWindowSize, 0));
        ImGui::SetNextWindowSize(ImVec2(imGuiWindowSize, 0));
        ImGui::Begin("DebugMenu", &showingDebugMenu);

		ImGui::Text("(F1) to close/open");
        ImGui::Spacing();

		// this is for displaying the framerates and delta time
        ImGui::Text("imgui fps: %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::Text("game delta time: %.3f ms", deltaTime);
        ImGui::Text("game fps: %.1f FPS", 1.0f / deltaTime);
        ImGui::Spacing();

		//this is for displaying the score
        ImGui::Text("distance score: %.1f", distanceScoreHolder->getScore());
        ImGui::Text("potion score: %.1f", potionScoreHolder->getScore());
        auto player = getGameObject("blocky");
        if (player) {
			short health = player->getComponent<HealthComponent>()->getHealthDebug();
            ImGui::Text("player health: %i", health);
        }
        ImGui::Spacing();

		static bool isCurrentlyUsingVision = true;
        if (isCurrentlyUsingVision) {
            if (ImGui::Button("Set Keyboard Input")) {
				auto player = getGameObject("blocky");
				if (player) {
					player->removeComponent<PlayerComponent>();
					player->addComponent(std::make_shared<PlayerComponent>(keyboardInput));
				}
				isCurrentlyUsingVision = false;
            }
        }
        else {
            if (ImGui::Button("Set Vision Input ")) {
                auto player = getGameObject("blocky");
                if (player) {
                    player->removeComponent<PlayerComponent>();
                    player->addComponent(std::make_shared<PlayerComponent>(visionInput));
                }
                isCurrentlyUsingVision = true;
            }
        }
        ImGui::Spacing();

		// this mess is for displaying game objects and their components
        if (ImGui::CollapsingHeader("Object list", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Reff counts (if increasing = memory leak)");
			ImGui::Text("ObjectReffecences: %i", DebugReferenceCounter::GetObjectReferenceCounter());
            ImGui::Text("ComponentReffecences: %i", DebugReferenceCounter::GetComponentReferenceCounter());
			ImGui::Spacing();
            ImGui::Text("amount of objects: %i", objects.size());
            ImGui::BeginChild("objects", ImVec2(0, 200), ImGuiChildFlags_FrameStyle);
            int index = 0;
            for (const auto& object : objects) {
                if (object) {
                    std::string objectTag = object->getTag();
                    if (objectTag.empty()) objectTag = "Unnamed";

                    std::string childId = "##object_child_" + std::to_string(index);
                    std::string label = "Object with tag: " + objectTag;

                    ImGui::Text("%s", label.c_str());

                    ImGui::BeginChild(childId.c_str(), ImVec2(0, 0), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeY);
                    for (const auto& name : object->getAllComponentNames()) {
                        ImGui::Text("    component: %s", name.c_str());
                    }
                    ImGui::EndChild();
                    ++index;
                }
            }
            ImGui::EndChild();
        }
        ImGui::Spacing();


		// this is for displaying the opencv camera view
        static GLuint textureID = 0;
        if (ImGui::CollapsingHeader("OpenCV Camera View", ImGuiTreeNodeFlags_DefaultOpen)) {
            float visionNormalisedPosition;
            {
                std::lock_guard<std::mutex> lock(vision::visionPositionMutex);
                visionNormalisedPosition = vision::visionNormalisedPosition;
            }
            ImGui::Text("vision position: %f ", visionNormalisedPosition);
            int imgSize = imGuiWindowSize - 20;
            GetTexFromVision(textureID, imgSize);
            ImGui::Image(textureID, ImVec2(imgSize, imgSize));
        }
        ImGui::Spacing();

        ImGui::End();
    }
}
#endif




