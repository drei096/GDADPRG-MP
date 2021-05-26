#include "OilSlick.h"
#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "StationaryBehavior.h"
#include "BGMovement.h"
#include "GameObjectManager.h"

OilSlick::OilSlick(string name) : ObjectPoolable(name)
{
}

void OilSlick::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("oil_slick"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setScale(0.05, 0.05);

	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -Game::WINDOW_HEIGHT * 50);
	//randomize position
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);


	Renderer* renderer = new Renderer("oilSlickSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);


	StationaryBehavior* behavior = new StationaryBehavior("OilBehavior", 400.0f);
	this->attachComponent(behavior);

	Collider* collide = new Collider("OilCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);

}

void OilSlick::onRelease()
{
	StationaryBehavior* behavior = (StationaryBehavior*)this->findComponentByName("OilBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % (int)2.0) + 1.0)), 0);
}

void OilSlick::onActivate()
{
	StationaryBehavior* behavior = (StationaryBehavior*)this->findComponentByName("OilBehavior");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	float posX = bgMove->laneCheck();
	this->getTransformable()->move(posX, 0);
}

ObjectPoolable* OilSlick::clone()
{
	ObjectPoolable* copyObj = new OilSlick(this->name);
	return copyObj;
}
