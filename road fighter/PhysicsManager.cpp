#include "PhysicsManager.h"
#include "Collider.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "UIText.h"
#include "ApplicationManager.h"
#include "BGMovement.h"
#include <iostream>
#include "LevelOverlay.h"
#include "SFXManager.h"

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
	else if (object->type == Collider::ObjectType::Fuel) {
		this->fuelCarObjects.push_back(object);
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
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	//cout << sharedInstance->playerObject[0]->getName() << endl;

	for (int x = 0; x < sharedInstance->enemyCarObjects.size(); x++)
	{
		sharedInstance->playerObject[0]->setAlreadyCollided(sharedInstance->playerObject[0]->willCollide(sharedInstance->enemyCarObjects[x]));
		//cout << sharedInstance->trackedObjects[0]->getName() << endl;
		if (sharedInstance->playerObject[0]->alreadyCollided() && (!sharedInstance->playerObject[0]->isChecked() && !sharedInstance->enemyCarObjects[x]->isChecked()))
		{
			sharedInstance->playerObject[0]->setChecked(true);
			sharedInstance->enemyCarObjects[x]->setChecked(true);
			
			//play nalang siguro ng lose sound dito kasi bawas pts ka
			//para ensured na 1 collision lang ang mangyayari sa car, kapag wala kasi to, multiple collisions mangyayari
			//ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)sharedInstance->enemyCarObjects[x]->getOwner());

			SFXManager::getInstance()->getSFX("collide")->play();

			bgMove->SPEED_MULTIPLIER = 200.0f;
			player->collisions++;
			player->speedCollision++;

			float yPosHolder = sharedInstance->enemyCarObjects[x]->getGlobalBounds().top + sharedInstance->enemyCarObjects[x]->getGlobalBounds().height;
			float xPosHolder = sharedInstance->playerObject[0]->getGlobalBounds().left - sharedInstance->playerObject[0]->getGlobalBounds().width;

			if (yPosHolder > sharedInstance->playerObject[0]->getGlobalBounds().top) {

				if (sharedInstance->playerObject[0]->getGlobalBounds().left < sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
					float placeholder = sharedInstance->enemyCarObjects[x]->getGlobalBounds().left - sharedInstance->playerObject[0]->getGlobalBounds().left;
					player->getTransformable()->move(-placeholder, 0);
				}
				else if (sharedInstance->playerObject[0]->getGlobalBounds().left > xPosHolder || sharedInstance->playerObject[0]->getGlobalBounds().left > sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
					float placeholder = sharedInstance->playerObject[0]->getGlobalBounds().left - sharedInstance->enemyCarObjects[x]->getGlobalBounds().left;
					player->getTransformable()->move(placeholder, 0);
				}
			}
			else{
				if (sharedInstance->playerObject[0]->getGlobalBounds().left < sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
					float placeholder = sharedInstance->enemyCarObjects[x]->getGlobalBounds().left - sharedInstance->playerObject[0]->getGlobalBounds().left;
					player->getTransformable()->move(-placeholder, 0);
				}
				else if (sharedInstance->playerObject[0]->getGlobalBounds().left > xPosHolder || sharedInstance->playerObject[0]->getGlobalBounds().left > sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
					float placeholder = sharedInstance->playerObject[0]->getGlobalBounds().left - sharedInstance->enemyCarObjects[x]->getGlobalBounds().left;
					player->getTransformable()->move(placeholder, 0);
				}
			}

			cout << "player collisions: " << player->collisions << endl;
			
			//cout << "Collide!" << endl;
		}
		else if (!sharedInstance->playerObject[0]->alreadyCollided() && (sharedInstance->playerObject[0]->isChecked() && sharedInstance->enemyCarObjects[x]->isChecked()))
		{
			sharedInstance->playerObject[0]->setChecked(false);
			sharedInstance->enemyCarObjects[x]->setChecked(false);
		}
	}

	/*
	for (int x = 0; x < sharedInstance->fuelCarObjects.size(); x++)
	{
		sharedInstance->playerObject[0]->setAlreadyCollided(sharedInstance->playerObject[0]->willCollide(sharedInstance->fuelCarObjects[x]));
		//cout << sharedInstance->trackedObjects[0]->getName() << endl;
		if (sharedInstance->playerObject[0]->alreadyCollided() && (!sharedInstance->playerObject[0]->isChecked() && !sharedInstance->fuelCarObjects[x]->isChecked()))
		{
			sharedInstance->playerObject[0]->setChecked(true);
			sharedInstance->fuelCarObjects[x]->setChecked(true);			

			cout << "player collisions: " << player->collisions << endl;

			//cout << "Collide!" << endl;
		}
		else if (!sharedInstance->playerObject[0]->alreadyCollided() && (sharedInstance->playerObject[0]->isChecked() && sharedInstance->enemyCarObjects[x]->isChecked()))
		{
			sharedInstance->playerObject[0]->setChecked(false);
			sharedInstance->enemyCarObjects[x]->setChecked(false);
		}
	}
	*/
}

void PhysicsManager::cleanUpObjects()
{
	playerObject.clear();
	enemyCarObjects.clear();
}
