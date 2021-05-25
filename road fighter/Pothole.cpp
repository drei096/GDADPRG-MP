#include "Pothole.h"
#include "TextureManager.h"
#include "Game.h"
#include "StationaryBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "BGMovement.h"
#include "GameObjectManager.h"


Pothole::Pothole(string name) : ObjectPoolable(name)
{
}

void Pothole::initialize()
{
	srand(time(NULL));
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("roadConditions"));

	sprite->setTextureRect(sf::IntRect(0, 0, 64, 64)); //crack from spritesheet
	sprite->setScale(0.5, 0.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(64 / 2, 64 / 2);
	sprite->setScale(0.4, 0.4);

	this->setPosition((Game::WINDOW_WIDTH / 2) - 20, -Game::WINDOW_HEIGHT * 50);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) , 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("PotholeSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);


	StationaryBehavior* behavior = new StationaryBehavior("PotholeBehavior", 400.0f);
	this->attachComponent(behavior);
	//behavior->configure(1.0f);


	Collider* collide = new Collider("PotholeCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
}

void Pothole::onRelease()
{
	StationaryBehavior* behavior = (StationaryBehavior*)this->findComponentByName("PotholeBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % (int)2.0) + 1.0)) , 0);
}

void Pothole::onActivate()
{
	//reset state
	StationaryBehavior* behavior = (StationaryBehavior*)this->findComponentByName("PotholeBehavior");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	float posX = bgMove->laneCheck();
	this->getTransformable()->move(posX, 0);
}

ObjectPoolable* Pothole::clone()
{
	ObjectPoolable* copyObj = new Pothole(this->name);
	return copyObj;
}
