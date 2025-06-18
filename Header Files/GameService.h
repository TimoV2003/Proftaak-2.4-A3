#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GameObject.h>

class GameObject;
__interface IScoreStrategy;

class GameService
{
private:
	GLFWwindow* window;
	glm::vec3 skyColor = glm::vec3(0.18f, 0.24f, 0.36f);
	glm::vec3 ambientLight = glm::vec3(0.6f, 0.6f, 0.6f);
	glm::vec3 diffuseLight = glm::vec3(0.6f, 0.6f, 0.6f);
	glm::vec3 lightPos = glm::vec3(1, 1, 1);
public:
	GameService(GLFWwindow* window) : window(window) {};
	~GameService() = default;
    
	// these functions are called from main
	void init();
	void update();
	void draw();
	void reset();
#ifdef _DEBUG
	void imgGuiUpdate();
#endif

	bool gameOver = false;
	bool gameOverMessageShown = false;

	// these functions are callable from game components via:
	// if(auto p = getParent()) { p->game->function(); }

	/// <summary>
	/// Adds gameObject to the updatable list.
	/// And inserts this service into the object.
	/// Always use this instead of manually adding it to the objects vertex.
	/// </summary>
	void instantiate(std::shared_ptr<GameObject> object);

	/// <summary>
	/// Gets the first gameObject with the given tag. or nullptr.
	/// store this object refference in a weak pointer when possible.
	/// </summary>
	/// <param name="tag">tag identifier of object you want to find</param>
	/// <returns>gameObject pointer or nullptr</returns>
	static std::shared_ptr<GameObject> getGameObject(std::string tag);

	/// <summary>
	/// queues given object to be deleted. best used on own object.
	/// </summary>
	void queueDelete(std::shared_ptr<GameObject>& object);

	/// <summary>
	/// Generates a random number between the given bounds
	/// </summary>
	static float RandomValue(float BoundryMin, float BoundryMax) {
		return BoundryMin + ((float)(rand()) / (float)(RAND_MAX)) * (BoundryMax - BoundryMin);
	}

	//TODO get gameObjects plural function
	//TODO queue delete based on tag

};

