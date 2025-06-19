#include "GameService.h"
#include <iostream>
#include <thread>

#include "AudioPlayer.h"
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
#include "ScoreStrategy.h"
#include "ColourDetection.h"
#include "MatToTexHelper.h" 

//this include section is needed for the components
#include "SpawnerComponent.h"
#include "MeshComponent.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "distanceScoreComponent.h"
#include "TreadmillComponent.h"
#include "WalkAnimationComponent.h"
#include "HealthUI.h"

// this include section is needed for the input strategy
#include "../patterns/strategy/interfaces/I_InputStrategy.h"
#include "../patterns/strategy/input_strategies/Headers/KeyboardInput.h"
#include "../patterns/strategy/input_strategies/Headers/VisionInput.h"

// this include section is needed for the Treadmill strategy
#include "../patterns/strategy/interfaces/IEndOfMillBehavior.h"
#include "../patterns/strategy/treadmill_strategies/Headers/FloorMillBehavior.h"

// this include section is needed for the Treadmill strategy
#include "../patterns/factory_method/Interfaces/GameEntityFactory.h"
#include "../patterns/factory_method/entity_factories/Headers/FloorFactory.h"
#include "../patterns/factory_method/entity_factories/Headers/HouseFactory.h"

using tigl::Vertex;

static bool showingDebugMenu = true;
static double lastFrameTime = 0;
static double deltaTime = 0.0f;

bool switchedFromLoadingTrack = false;

//Game Object Variables
std::vector<std::shared_ptr<GameObject>> objects;
std::vector<std::shared_ptr<GameObject>> pendingAdding;
std::vector<std::shared_ptr<GameObject>> pendingDeletion;

//Input Variables
std::shared_ptr<IInputStrategy> keyboardInput;
std::shared_ptr<IInputStrategy> visionInput;

//Mill Variables
std::shared_ptr<IEndOfMillBehavior> floormillBehavior;

//Score Variables
std::shared_ptr<ScoreStrategy> distanceScoreHolder;
std::shared_ptr<ScoreStrategy> potionScoreHolder;

//Factory Variables
std::shared_ptr<GameEntityFactory> houseFactory;
std::shared_ptr<GameEntityFactory> floorFactory;


void GameService::init() {
    keyboardInput = std::make_shared<KeyboardInput>();
    visionInput = std::make_shared<VisionInput>();
	distanceScoreHolder = std::make_shared<ScoreStrategy>();
	potionScoreHolder = std::make_shared<ScoreStrategy>();
	floormillBehavior = std::make_shared<FloorMillBehavior>();
    houseFactory = std::make_shared<HouseFactory>();
    floorFactory = std::make_shared<FloorFactory>();

    if (switchedFromLoadingTrack == false) {
        stopMusicThread = false;
        playMusicInThread("Resource Files/Soundtrack/Gamecube.mp3");
    }
    

    /////  GAME OBJECT CREATION  /////
    Model PlayerModel;
    if (ModelLoader::load("Resource Files/PlayerModel/PlayerPlauge.obj", PlayerModel)) { // Make sure this path is correct
        auto blocky = std::make_shared<GameObject>("blocky",2);
        blocky->position = glm::vec3(0, 0, 6);
        blocky->scale = glm::vec3(0.7f, 0.7f, 0.7f);
        blocky->addComponent(std::make_shared<PlayerComponent>(visionInput));
        blocky->addComponent(std::make_shared<MeshComponent>(PlayerModel));
		auto healthComponent = std::make_shared<HealthComponent>(5, 1.0f);
        blocky->addComponent(healthComponent);
		blocky->addComponent(std::make_shared<HealthUI>(healthComponent, window));
		blocky->addComponent(std::make_shared<WalkAnimationComponent>());
		blocky->addComponent(std::make_shared<DistanceScoreComponent>(distanceScoreHolder));
        instantiate(blocky);
    }
    

    for (size_t i = 0; i < 4; i++) {
        auto ground = floorFactory->CreateEntity();
        ground->position = glm::vec3(0, -1, 50.0f + (i * -50.0f));
        instantiate(ground);
    }
    for (size_t i = 0; i < 10; i++) {
        auto house = houseFactory->CreateEntity();
        house->position = glm::vec3(-20, -1, 20.0f + (i * -20.0f));
        house->rotation = glm::vec3(0.0f, 1.57f, 0.0f);
        instantiate(house);
    }
    for (size_t i = 0; i < 10; i++) {
        auto house = houseFactory->CreateEntity();
        house->position = glm::vec3(20, -1, 20.0f + (i * -20.0f));
        house->rotation = glm::vec3(0.0f, -1.57f, 0.0f);
        instantiate(house);
    }

    auto testSpawner = std::make_shared<GameObject>("testSpawner");
    float Spawnerdistance = -50.0f;
    testSpawner->position = glm::vec3(0, 0, Spawnerdistance);
    testSpawner->addComponent(std::make_shared<SpawnerComponent>(1.0f, 5.0f));
    instantiate(testSpawner);

    objects.insert(objects.end(), pendingAdding.begin(), pendingAdding.end());
	pendingAdding.clear();
}

void GameService::update() {
    if (!switchedFromLoadingTrack) {
        switchMusic("Resource Files/Soundtrack/Faint Glow.mp3");
		switched = true;
    }

    double currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    for (auto& object : objects) {
        object->update((float)deltaTime);
    }

    //add new objects
    if (!pendingAdding.empty()) {
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

void GameService::draw() {
    glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    tigl::shader->use();
    glm::mat4 modelMatrix(1);
    glm::mat4 viewMatrix(1);

    //GPT aspect ratio code. please make propper
    int width, height;
    glfwGetFramebufferSize(this->window, &width, &height);
    float aspect = width / (float)height;

    tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f));
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
    tigl::shader->setModelMatrix(modelMatrix);
    tigl::shader->enableColor(false);
    tigl::shader->enableFog(true);
    tigl::shader->setFogColor(skyColor);
    tigl::shader->enableLighting(true);
    tigl::shader->setLightCount(1);
    tigl::shader->setLightDirectional(0, true);
    tigl::shader->setLightPosition(0, lightPos);
    tigl::shader->setLightAmbient(0, ambientLight);
    tigl::shader->setLightDiffuse(0, diffuseLight);

    for (auto& object : objects) {
        tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f));
        tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
        tigl::shader->setModelMatrix(modelMatrix);
        tigl::shader->enableColor(false);
        object->draw();
    }

    // sub-optimal, but this forces ui to be drawn last
	auto player = GameService::getGameObject("blocky");
    if (player) {
        auto ui = player->getComponent<HealthUI>();
		if (ui) {
			ui->draw();
		}
    }
}

void GameService::instantiate(std::shared_ptr<GameObject> object) {
    //TODO add nullptr check, should to this to a lot of functions
    object->setGameService(this);
    pendingAdding.push_back(object);
}

//TODO not tested, but should work
std::shared_ptr<GameObject> GameService::getGameObject(std::string tag) {
    for (auto& object : objects) {
        if (tag == object->getTag()) return object;
    }
    return nullptr;
}

void GameService::reset() {
	objects.clear();
	pendingAdding.clear();
	pendingDeletion.clear();
    init();
	this->gameOverMessageShown = false;
    }

void GameService::queueDelete(std::shared_ptr<GameObject>& object) {
    // find = return index of first find or index of end (last index + 1)
    // so if find == vector.end() then nothing was found
    if (std::find(pendingDeletion.begin(), pendingDeletion.end(), object) == pendingDeletion.end()) {
        pendingDeletion.push_back(object);
    }
}

void GameService::playMusicInThread(const std::string& filepath) {
    stopMusicThread = false;
    musicThread = std::thread([this, filepath]() {
        if (audioPlayer.load(filepath)) {
            audioPlayer.play();

            while (!stopMusicThread) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            audioPlayer.stop();
        }
        else {
            std::cerr << "Failed to load: " << filepath << std::endl;
        }
        });
}

void GameService::switchMusic(const std::string& newTrackPath) {
    stopMusicThread = true;
    if (musicThread.joinable())
        musicThread.join();

    playMusicInThread(newTrackPath);
}

GameService::~GameService() {
    stopMusicThread = true;
    if (musicThread.joinable())
    {
        musicThread.join();
    }
}

#ifdef _DEBUG
void GameService::imgGuiUpdate() {
    static int lastKeyCode = -1;
    int keyPressed = glfwGetKey(this->window, GLFW_KEY_F1);
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
            ImGui::Image(textureID, ImVec2((float)imgSize, (float)imgSize));
        }
        ImGui::Spacing();

        ImGui::End();
    }
}
#endif



