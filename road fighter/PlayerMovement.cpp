#include "PlayerMovement.h"
#include "GameObject.h"
#include "PlayerInputController.h"
#include "BGMovement.h"
#include "EmptyGameObject.h"
#include "GameObjectManager.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "ObjectPoolable.h"
#include "EnemyCar.h"
#include "PlayerCar.h"
#include "Game.h"
#include "SFXManager.h"
#include <iostream>

PlayerMovement::PlayerMovement(string name) : ObjectComponent(name, Script)
{
}

PlayerMovement::~PlayerMovement()
{
	ObjectComponent::~ObjectComponent();
}

void PlayerMovement::perform()
{
	PlayerInputController* inputController = (PlayerInputController*)this->getOwner()->getComponentsOfType(componentType::Input)[0];
	Transformable* playerTransformable = this->getOwner()->getTransformable();
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	PlayerCar* playerCar = (PlayerCar*)this->getOwner();

	if (playerTransformable == NULL || inputController == NULL) 
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	Vector2f offset(0.0f, 0.0f);

	if (inputController->isSecondGear()) 
	{
		bgMove->SPEED_MULTIPLIER += this->SPEED_MULTIPLIER * deltaTime.asSeconds();

		if (bgMove->SPEED_MULTIPLIER >= 1000.0f) {
			bgMove->SPEED_MULTIPLIER = 1000.0f;
		}
		if (bgMove->SPEED_MULTIPLIER <= 0.0f) {
			bgMove->SPEED_MULTIPLIER = 0.0f;
		}
		//cout << offset.x << " " << offset.y << endl;
		//offset.y -= this->SPEED_MULTIPLIER;
		//playerTransformable->move(offset * deltaTime.asSeconds());

		if (inputController->isRight())
		{
			this->ticks += this->deltaTime.asSeconds();
			//this->resetSpeedMultiplier();
			if (playerTransformable->getPosition().x >= ((Game::WINDOW_WIDTH / 2) + 40)) {
				playerTransformable->setPosition(playerTransformable->getPosition());
				if (this->ticks > 0.5f) {
					SFXManager::getInstance()->getSFX("collide")->play();
					playerCar->getTransformable()->move(-20, 0);
					playerCar->collisions++;
					playerCar->speedCollision++;
					this->ticks = 0;
				}
			}

			else {
				offset.x += this->SPEED_MULTIPLIER;
				playerTransformable->move(offset * deltaTime.asSeconds());
			}
		}

		else if (inputController->isLeft())
		{
			this->ticks += this->deltaTime.asSeconds();
			//this->resetSpeedMultiplier();
			if (playerTransformable->getPosition().x <= ((Game::WINDOW_WIDTH / 2) - 90)) {
				playerTransformable->setPosition(playerTransformable->getPosition());
				if (this->ticks > 0.5f) {
					SFXManager::getInstance()->getSFX("collide")->play();
					playerCar->getTransformable()->move(20, 0);
					playerCar->collisions++;
					playerCar->speedCollision++;
					this->ticks = 0;
				}
			}

			else {
				offset.x -= this->SPEED_MULTIPLIER;
				playerTransformable->move(offset * deltaTime.asSeconds());
			}
		}
	}

	/*
	else if (inputController->isRight()) 
	{
		//this->resetSpeedMultiplier();
		if (playerTransformable->getPosition().x >= ((Game::WINDOW_WIDTH / 2) + 40)) {
			playerTransformable->setPosition(playerTransformable->getPosition());
		}

		else {
			offset.x += this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
	else if (inputController->isLeft()) 
	{
		//this->resetSpeedMultiplier();
		if (playerTransformable->getPosition().x <= ((Game::WINDOW_WIDTH / 2) - 90)) {
			playerTransformable->setPosition(playerTransformable->getPosition());
		}

		else {
			offset.x -= this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
	*/

	else if (!inputController->isSecondGear())
	{

		bgMove->SPEED_MULTIPLIER -= this->SPEED_MULTIPLIER * deltaTime.asSeconds() * 2;

		if (bgMove->SPEED_MULTIPLIER >= 1000.0f) {
			bgMove->SPEED_MULTIPLIER = 1000.0f;
		}
		if (bgMove->SPEED_MULTIPLIER <= 0.0f) {
			bgMove->SPEED_MULTIPLIER = 0.0f;
		}


		cout << bgMove->SPEED_MULTIPLIER << endl;
		//cout << offset.x << " " << offset.y << endl;
		//offset.y -= this->SPEED_MULTIPLIER;
		//playerTransformable->move(offset * deltaTime.asSeconds());

		if (inputController->isRight())
		{
			this->ticks += this->deltaTime.asSeconds();
			//this->resetSpeedMultiplier();
			if (playerTransformable->getPosition().x >= ((Game::WINDOW_WIDTH / 2) + 40)) {
				playerTransformable->setPosition(playerTransformable->getPosition());
				if (this->ticks > 0.5f) {
					SFXManager::getInstance()->getSFX("collide")->play();
					playerCar->getTransformable()->move(-20, 0);
					playerCar->collisions++;
					playerCar->speedCollision++;
					this->ticks = 0;
				}
			}

			else {
				offset.x += this->SPEED_MULTIPLIER;
				playerTransformable->move(offset * deltaTime.asSeconds());
			}
		}

		else if (inputController->isLeft())
		{
			this->ticks += this->deltaTime.asSeconds();
			//this->resetSpeedMultiplier();
			if (playerTransformable->getPosition().x <= ((Game::WINDOW_WIDTH / 2) - 90)) {
				playerTransformable->setPosition(playerTransformable->getPosition());
				if (this->ticks > 0.5f) {
					SFXManager::getInstance()->getSFX("collide")->play();
					playerCar->getTransformable()->move(20, 0);
					playerCar->collisions++;
					playerCar->speedCollision++;
					this->ticks = 0;
				}
			}

			else {
				offset.x -= this->SPEED_MULTIPLIER;
				playerTransformable->move(offset * deltaTime.asSeconds());
			}
		}
	}
}

/*
void PlayerMovement::resetSpeedMultiplier()
{
	this->SPEED_MULTIPLIER = 300.0f;
}
*/