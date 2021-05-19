#pragma once
#include "ObjectComponent.h"
#include "GameObject.h"
#include <unordered_map>
#include <vector>
#include "Collider.h"

typedef std::vector<Collider*> CollisionList;

class PhysicsManager : public ObjectComponent
{
public:

	static void initialize(string name, GameObject* parent);
	static void destroy();
	static PhysicsManager* getInstance();
	~PhysicsManager();

	void trackObject(Collider* object);
	void untrackObject(Collider* object);
	void clearAll();
	void perform();

private:
	PhysicsManager(string name) : ObjectComponent(name, Script) {};
	PhysicsManager(PhysicsManager const&) : ObjectComponent(name, Script) {};             // copy constructor is private
	PhysicsManager& operator=(PhysicsManager const&) {};  // assignment operator is private
	static PhysicsManager* sharedInstance;
	float ticks;

	CollisionList playerObject;
	CollisionList enemyCarObjects;
	CollisionList forCleaningObjects;

	void cleanUpObjects();
};

