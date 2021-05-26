#include "NormalEnemyBehavior.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "UIText.h"
#include "LevelOverlay.h"
#include "BGMovement.h"

/*
* This behavior class is about cars only at one lane and does not go to other lanes
*/

NormalEnemyBehavior::NormalEnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void NormalEnemyBehavior::perform()
{
	//inititalize the to be accessed values
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");


	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	//bool check the position of the instantiated car
	if (transformable->getPosition().y > -400) {

		if (transformable->getPosition().x < 317.5)
		{
			bgMove->leftMost = true;
			this->position = LeftMost;
		}
		else if (transformable->getPosition().x >= 317.5 && transformable->getPosition().x < 350)
		{
			bgMove->left = true;
			this->position = Left;

		}
		else if (transformable->getPosition().x <= 382.5 && transformable->getPosition().x > 350)
		{
			bgMove->right = true;
			this->position = Right;

		}
		else if (transformable->getPosition().x > 382.5)
		{
			bgMove->rightMost = true;
			this->position = RightMost;
		}
	}

	//move forward
	if (this->movementType == Forward) {

		//check if the player is going forward
		if (inputController->isSecondGear())
		{
			//start is ticked to true if enemy car is inside the window
			if (transformable->getPosition().y > 0) {
				this->isStart = true;
			}
			//gives the illusion of player being faster than the enemy cars but actually the enemies are going downwards
			transformable->move(0, this->deltaTime.asSeconds()* SPEED_MULTIPLIER);
			//checked if the player has passed the enemy car
			if (transformable->getPosition().y > player->getTransformable()->getPosition().y && !this->passed) {
				if (this->owner->getName() != "enemyFuel") {
					player->passedCar++;
				}
				this->passed = true;
			}
		}
		else
		{
			//if player is not going forward or at a standstill
			//enemies go upwards which gives the illusion of player slowing down
			transformable->move(0, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER * 0.8);
			//checked if the player has passed the enemy car
			if (transformable->getPosition().y < player->getTransformable()->getPosition().y && this->passed) {
				if (this->owner->getName() != "enemyFuel") {
					player->passedCar--;
				}
				this->passed = false;
			}
		}

		
		//check if position is out of bounds, we can delete/return to pool
		if ((transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) && this->isStart) {
			//if owner is red car
			if (this->owner->getName() == "enemy") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
				this->isStart = false;
			}
			//if owner is fuel car
			else if (this->owner->getName() == "enemyFuel") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
				this->isStart = false;
			}

			//check current position and set the corresponding lane checker in bgmovement to false
			if (this->position == LeftMost)
			{
				bgMove->leftMost = false;
			}
			else if (this->position == Left)
			{
				bgMove->left = false;

			}
			else if (this->position == Right)
			{
				bgMove->right = false;

			}
			else if (this->position == RightMost)
			{
				bgMove->rightMost = false;
			}
		}
		

	}


}

void NormalEnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void NormalEnemyBehavior::reset()
{
	this->movementType = Forward;
	this->ticks = 0.0f;
	this->passed = false;
}

