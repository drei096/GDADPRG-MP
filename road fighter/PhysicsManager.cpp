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
	if (object->type == Collider::ObjectType::Player) {
		sharedInstance->playerObject.erase(std::remove(playerObject.begin(), playerObject.end(), object), playerObject.end());
		sharedInstance->playerObject.shrink_to_fit();
	}
	else if (object->type == Collider::ObjectType::EnemyCar) {
		sharedInstance->enemyCarObjects.erase(std::remove(enemyCarObjects.begin(), enemyCarObjects.end(), object), enemyCarObjects.end());
		sharedInstance->enemyCarObjects.shrink_to_fit();
	}
	else if (object->type == Collider::ObjectType::Fuel) {
		sharedInstance->fuelCarObjects.erase(std::remove(fuelCarObjects.begin(), fuelCarObjects.end(), object), fuelCarObjects.end());
		sharedInstance->fuelCarObjects.shrink_to_fit();
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
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	
	//cout << sharedInstance->playerObject[0]->getName() << endl;

	for (int x = 0; x < sharedInstance->enemyCarObjects.size(); x++)
	{
		sharedInstance->playerObject[0]->setAlreadyCollided(sharedInstance->playerObject[0]->willCollide(sharedInstance->enemyCarObjects[x]));
		//cout << sharedInstance->trackedObjects[0]->getName() << endl;

		//FORMER SNIPPET FOR SCORE UPDATER
		/*
		if (sharedInstance->playerObject[0]->getGlobalBounds().top < sharedInstance->enemyCarObjects[x]->getGlobalBounds().top)
		{
			//cout << "overtake" << endl;
			player->hasPassedACar = true;
			//levelOverlay->score = levelOverlay->score + 50;
			//textScore->setText("SCORE\n" + (to_string)(levelOverlay->score));
		}
		*/

		if (sharedInstance->playerObject[0]->alreadyCollided() && (!sharedInstance->playerObject[0]->isChecked() && !sharedInstance->enemyCarObjects[x]->isChecked()))
		{
			//tick collision bool
			sharedInstance->playerObject[0]->setChecked(true);
			sharedInstance->enemyCarObjects[x]->setChecked(true);
			


			bgMove->SPEED_MULTIPLIER = 200.0f;
			player->collisions++;
			player->speedCollision++;

			if (sharedInstance->enemyCarObjects[x]->getOwner()->getName() != "oil") {

				SFXManager::getInstance()->getSFX("collide")->play();

				//bottom boundary
				float yPosHolder = sharedInstance->enemyCarObjects[x]->getGlobalBounds().top + sharedInstance->enemyCarObjects[x]->getGlobalBounds().height;
				float xPosHolder = sharedInstance->playerObject[0]->getGlobalBounds().left - sharedInstance->playerObject[0]->getGlobalBounds().width;

				//if bottom boundary of enemy car is higher than the player car
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
				//if bottom boundary of enemy car is lower than the player car
				else {
					if (sharedInstance->playerObject[0]->getGlobalBounds().left < sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
						float placeholder = sharedInstance->enemyCarObjects[x]->getGlobalBounds().left - sharedInstance->playerObject[0]->getGlobalBounds().left;
						player->getTransformable()->move(-placeholder, 0);
					}
					else if (sharedInstance->playerObject[0]->getGlobalBounds().left > xPosHolder || sharedInstance->playerObject[0]->getGlobalBounds().left > sharedInstance->enemyCarObjects[x]->getGlobalBounds().left) {
						float placeholder = sharedInstance->playerObject[0]->getGlobalBounds().left - sharedInstance->enemyCarObjects[x]->getGlobalBounds().left;
						player->getTransformable()->move(placeholder, 0);
					}
				}
			}

			else {
				//sound cue if collided with oil
				SFXManager::getInstance()->getSFX("skid")->play();
			}
			
		}
		else if (!sharedInstance->playerObject[0]->alreadyCollided() && (sharedInstance->playerObject[0]->isChecked() && sharedInstance->enemyCarObjects[x]->isChecked()))
		{
			//untick collision bool
			sharedInstance->playerObject[0]->setChecked(false);
			sharedInstance->enemyCarObjects[x]->setChecked(false);
		}
	}

	
	for (int x = 0; x < sharedInstance->fuelCarObjects.size(); x++)
	{
		sharedInstance->playerObject[0]->setAlreadyCollided(sharedInstance->playerObject[0]->willCollide(sharedInstance->fuelCarObjects[x]));
		if (sharedInstance->playerObject[0]->alreadyCollided() && (!sharedInstance->playerObject[0]->isChecked() && !sharedInstance->fuelCarObjects[x]->isChecked()))
		{
			//tick collision bool
			sharedInstance->playerObject[0]->setChecked(true);
			sharedInstance->fuelCarObjects[x]->setChecked(true);
			//sound cue
			SFXManager::getInstance()->getSFX("coin")->play();
			
			//remove object
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG)->releasePoolable((ObjectPoolable*)sharedInstance->fuelCarObjects[x]->getOwner());

			player->bonus++;

		}
		else if (!sharedInstance->playerObject[0]->alreadyCollided() && (sharedInstance->playerObject[0]->isChecked() && sharedInstance->fuelCarObjects[x]->isChecked()))
		{
			//untick collision bool
			sharedInstance->playerObject[0]->setChecked(false);
			sharedInstance->fuelCarObjects[x]->setChecked(false);
		}
		
	}

}

void PhysicsManager::cleanUpObjects()
{
	playerObject.clear();
	enemyCarObjects.clear();
	fuelCarObjects.clear();
}

