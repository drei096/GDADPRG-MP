#include "EnemyBehavior.h"
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
* This behavior class is about the cars moving side to side randomly at a certain amount of time they are in the map
*/
EnemyBehavior::EnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void EnemyBehavior::perform()
{
	//inititalize the to be accessed values
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");


	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	//if it goes out of bounds on right side
	if (transformable->getPosition().x >= ((Game::WINDOW_WIDTH / 2) + 40)) {
		transformable->setPosition((Game::WINDOW_WIDTH / 2) + 40, transformable->getPosition().y);
	}
	//if it goes out of bounds on left side
	if (transformable->getPosition().x <= ((Game::WINDOW_WIDTH / 2) - 90)) {
		transformable->setPosition((Game::WINDOW_WIDTH / 2) - 90, transformable->getPosition().y);
	}

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

	//if movement type is forward
	if (this->movementType == Forward) {


		//check if the player is going forward
		if (inputController->isSecondGear())
		{
			//start is ticked to true if enemy car is inside the window
			if (transformable->getPosition().y > 0) {
				this->isStart = true;
			}
			//gives the illusion of player being faster than the enemy cars but actually the enemies are going downwards
			transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER); 
			//checked if the player has passed the enemy car
			if (transformable->getPosition().y > player->getTransformable()->getPosition().y && !this->passed) {
				player->passedCar++;
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
				player->passedCar--;
				this->passed = false;
			}
		}

		//check if position is out of bounds, we can delete/return to pool
		if ((transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) && this->isStart) {
			//if owner is cyan car
			if (this->getOwner()->getName() == "enemyCyan") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
				this->isStart = false;
			}
			//if owner is truck
			else if (this->getOwner()->getName() == "enemyTruck") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
				this->isStart = false;
			}
			//if owner is yellow
			else if (this->getOwner()->getName() == "enemyYellow") {
				ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
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
		
		
		
		//IF GOING TO SIDE OR NOT
		if (this->ticks >= 0.5f && !this->isMoved && this->goSide)
		{
			this->movementType = Side;
			this->ticks = 0;
			this->prevX = transformable->getPosition().x;
			this->isMoved = true;

		}
		
	}

	else if (this->movementType == Side)
	{
			//LEFTMOST
			if (this->prevX < 317.5)
			{
				bgMove->leftMost = false;
				if(inputController->isSecondGear())
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
				else
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER);

				//GO 1 STEP RIGHT
				if (this->sideChoice == 0) {
					if (transformable->getPosition().x >= this->prevX + 32.5) {
						transformable->setPosition(this->prevX + 32.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 2 STEPS RIGHT
				else if (this->sideChoice == 1) {
					if (transformable->getPosition().x >= this->prevX + 97.5) {
						transformable->setPosition(this->prevX + 97.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 3 STEPS RIGHT
				else if (this->sideChoice == 2) {
					if (transformable->getPosition().x >= this->prevX + 130) {
						transformable->setPosition(this->prevX + 130, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
			}
			//LEFT
			else if (this->prevX >= 317.5 && this->prevX < 350)
			{
				bgMove->left = false;
				//GO 1 STEP RIGHT
				if (this->sideChoice == 0) {
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x >= this->prevX + 65) {
						transformable->setPosition(this->prevX + 65, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 2 STEPS RIGHT
				else if (this->sideChoice == 1) {
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x >= this->prevX + 97.5) {
						transformable->setPosition(this->prevX + 97.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 1 STEP LEFT
				else if (this->sideChoice == 2) {
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x <= this->prevX - 32.5) {
						transformable->setPosition(this->prevX - 32.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
			}
			//RIGHTMOST
			else if (this->prevX > 382.5)
			{
				bgMove->rightMost = false;
				if (inputController->isSecondGear())
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, this->deltaTime.asSeconds()* SPEED_MULTIPLIER);
				else
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);

				//GO 1 STEP LEFT
				if (this->sideChoice == 0) {
					if (transformable->getPosition().x <= this->prevX - 32.5) {
						transformable->setPosition(this->prevX - 32.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 2 STEPS LEFT
				else if (this->sideChoice == 1) {
					if (transformable->getPosition().x <= this->prevX - 97.5) {
						transformable->setPosition(this->prevX - 97.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 3 STEPS LEFT
				else if (this->sideChoice == 2) {
					if (transformable->getPosition().x <= this->prevX - 130) {
						transformable->setPosition(this->prevX - 130, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
			}
			//RIGHT
			else if (this->prevX <= 382.5 && this->prevX > 350)
			{
				bgMove->right = false;
				//GO 1 STEP LEFT
				if (this->sideChoice == 0) {
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x <= this->prevX - 65) {
						transformable->setPosition(this->prevX - 65, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 2 STEPS LEFT
				else if (this->sideChoice == 1) {
					transformable->move(this->deltaTime.asSeconds() * -SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x <= this->prevX - 97.5) {
						transformable->setPosition(this->prevX - 97.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
				//GO 1 STEP RIGHT
				else if (this->sideChoice == 2) {
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, 0);
					if (transformable->getPosition().x >= this->prevX + 32.5) {
						transformable->setPosition(this->prevX + 32.5, transformable->getPosition().y);
						this->movementType = Forward;
					}
				}
			}

	}


}

void EnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior::reset()
{
	this->movementType = Forward;
	this->ticks = 0.0f;
	this->isMoved = false;
	this->passed = false;
	//RANDOMIZER OF LANE CHOICE
	this->sideChoice = rand() % 3;\
	//RANDOMIZER IF GOING TO CHANGE LANES OR NOT
	this->goSide = ((rand() % 2 == 0) ? true : false);
}
