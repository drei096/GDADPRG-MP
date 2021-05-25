#include "StationaryBehavior.h"
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

StationaryBehavior::StationaryBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void StationaryBehavior::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	//this->movementType = Side;


	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	/*if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}*/

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

	if (this->movementType == Forward) {

		if (inputController->isSecondGear())
		{
			if (transformable->getPosition().y > 0) {
				this->isStart = true;
			}
			transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
		}
		else
		{
			transformable->move(0, 0);
		}

		
		//check if position is out of bounds, we can delete/return to pool
		if ((transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) && this->isStart) {

			if (this->owner->getName() == "pothole") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POTHOLE_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
				this->isStart = false;
			}

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

void StationaryBehavior::configure(float delay)
{
	this->delay += delay;
}

void StationaryBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	//this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}
