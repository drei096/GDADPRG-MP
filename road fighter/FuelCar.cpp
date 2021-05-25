#include "FuelCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "NormalEnemyBehavior.h"
#include "BGMovement.h"
#include "GameObjectManager.h"

FuelCar::FuelCar(string name) : ObjectPoolable(name)
{

}

void FuelCar::initialize()
{
	srand(time(NULL));
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("enemyCivCars"));

	sprite->setTextureRect(sf::IntRect(40, 0, 250, 340)); //rainbow car from spritesheet
	sprite->setScale(0.5, 0.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(300 / 2, 340 / 2);
	sprite->setScale(0.12, 0.12);

	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -Game::WINDOW_HEIGHT * 50);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemyFuelSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	NormalEnemyBehavior* behavior = new NormalEnemyBehavior("EnemyFuelBehavior", 400.0f);
	this->attachComponent(behavior);
	//behavior->configure(1.0f);


	Collider* fcollide = new Collider("FuelCollide", sprite, Collider::ObjectType::Fuel);
	this->attachComponent(fcollide);
	PhysicsManager::getInstance()->trackObject(fcollide);

}

void FuelCar::onRelease()
{
	NormalEnemyBehavior* behavior = (NormalEnemyBehavior*)this->findComponentByName("EnemyFuelBehavior");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -Game::WINDOW_HEIGHT * 20);
	//randomize
	int sign = rand() % 2;
	float available = (65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1);
	this->getTransformable()->move(available, 0);
	this->setEnabled(false);
}

void FuelCar::onActivate()
{
	//reset state
	NormalEnemyBehavior* behavior = (NormalEnemyBehavior*)this->findComponentByName("EnemyFuelBehavior");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	float posX = bgMove->laneCheck();
	this->getTransformable()->move(posX, 0);
	this->setEnabled(false);
}

ObjectPoolable* FuelCar::clone()
{
	ObjectPoolable* copyObj = new FuelCar(this->name);
	return copyObj;
}
