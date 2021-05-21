#include "FuelCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"

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
	sprite->setScale(0.1, 0.1);

	this->setPosition((rand()%(Game::WINDOW_WIDTH / 2) - 25), Game::WINDOW_HEIGHT);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemyFuelSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehavior* behavior = new EnemyBehavior("EnemyFuelBehavior", 400.0f);
	this->attachComponent(behavior);
	behavior->configure(1.0f);


	Collider* collide = new Collider("EnemyCollide", sprite, Collider::ObjectType::Fuel);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
}

void FuelCar::onRelease()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyFuelBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
}

void FuelCar::onActivate()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyFuelBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
}

ObjectPoolable* FuelCar::clone()
{
	ObjectPoolable* copyObj = new FuelCar(this->name);
	return copyObj;
}