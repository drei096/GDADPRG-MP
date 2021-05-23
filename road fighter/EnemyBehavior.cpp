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

EnemyBehavior::EnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void EnemyBehavior::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");

	//this->movementType = Side;

	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	
	//cout << (Game::WINDOW_WIDTH / 2) - 25 << endl;

	/*if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}*/
	
	//cout << player->passedCar << endl;

	if (this->movementType == Forward) {

		if (inputController->isSecondGear())
		{
			transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER); 
			if (transformable->getPosition().y > player->getTransformable()->getPosition().y && !this->passed) {
				player->passedCar++;
				this->passed = true;
			}
		}
		else
		{
			transformable->move(0, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER * 0.8);
			if (transformable->getPosition().y < player->getTransformable()->getPosition().y && this->passed) {
				player->passedCar--;
				this->passed = false;
			}
		}

		//check if position is out of bounds, we can delete/return to pool
		if (transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) {
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			/*
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			*/
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			//ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POTHOLE_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			
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
				if(inputController->isSecondGear())
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
				else
					transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER);

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
			//SECONDARY LEFT
			else if (this->prevX >= 317.5 && this->prevX < 350)
			{
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
			//SECONDARY RIGHT
			else if (this->prevX <= 382.5 && this->prevX > 350)
			{
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

	//TEMPORARY: just here to check if setEnabled flags work
	/*if (this->ticks > this->delay) {
		this->getOwner()->setEnabled(false);
	}*/

}

void EnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	//this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
	this->sideChoice = rand() % 3;
	this->isMoved = false;
	this->passed = false;
	this->goSide = ((rand() % 2 == 0) ? true : false);
}
