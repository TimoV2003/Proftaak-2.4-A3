#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GameObject.h>

class GameObject;

class GameService
{
private:
	GLFWwindow* window;

public:
	GameService(GLFWwindow* window) : window(window) {}
	~GameService() = default;

	// these functions are called from main
	void init();
	void update();
	void draw();


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
	};

	//TODO get gameObjects plural function
	//TODO queue delete based on tag


};

