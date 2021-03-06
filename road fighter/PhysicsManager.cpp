#include "PhysicsManager.h"
#include "Collider.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "UIText.h"
#include "ApplicationManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = NULL;

void PhysicsManager::initialize(string name, GameObject* parent)
{
	PhysicsManager* physicsMan = new PhysicsManager(name);
	parent->attachComponent(physicsMan);
}

void PhysicsManager::destroy()
{
	sharedInstance = NULL;
}

PhysicsManager* PhysicsManager::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new PhysicsManager("p6Manager");
	}
	return sharedInstance;
}

PhysicsManager::~PhysicsManager()
{
	ObjectComponent::~ObjectComponent();
}

void PhysicsManager::trackObject(Collider* object)
{
	if (object->type == Collider::ObjectType::Player) {
		this->playerObject.push_back(object);
	}
	else if (object->type == Collider::ObjectType::EnemyCar) {
		this->enemyCarObjects.push_back(object);
	}
}

void PhysicsManager::untrackObject(Collider* object)
{
	/*
	delete object;
	if (object->type == Collider::ObjectType::Player) {
		this->playerObject.erase(std::remove(playerObject.begin(), playerObject.end(), object), playerObject.end());
		this->playerObject.shrink_to_fit();
	}
	else if (object->type == Collider::ObjectType::Bullet) {
		this->bulletObjects.erase(std::remove(bulletObjects.begin(), bulletObjects.end(), object), bulletObjects.end());
		this->bulletObjects.shrink_to_fit();
	}
	else if (object->type == Collider::ObjectType::Enemy) {
		this->enemyCarObjects.erase(std::remove(enemyCarObjects.begin(), enemyCarObjects.end(), object), enemyCarObjects.end());
		this->enemyCarObjects.shrink_to_fit();
	}
	*/
}

void PhysicsManager::clearAll()
{
	cleanUpObjects();
}

void PhysicsManager::perform()
{
	//cout << sharedInstance->playerObject[0]->getName() << endl;

	for (int x = 0; x < sharedInstance->enemyCarObjects.size(); x++)
	{
		//cout << sharedInstance->trackedObjects[0]->getName() << endl;
		if (sharedInstance->playerObject[0]->willCollide(sharedInstance->enemyCarObjects[x]))
		{
			/*
			DeathPopUp* deathPopUp = new DeathPopUp("deathPopUp");
			GameObjectManager::getInstance()->addObject(deathPopUp);
			*/
			ApplicationManager::getInstance()->pauseApplication();
			//cout << "Collide!" << endl;
		}
	}
	enemyCarObjects.clear();
}

void PhysicsManager::cleanUpObjects()
{
	playerObject.clear();
	enemyCarObjects.clear();
}
