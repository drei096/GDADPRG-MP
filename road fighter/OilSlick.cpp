#include "OilSlick.h"
#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"

OilSlick::OilSlick(string name) : ObjectPoolable(name)
{
}

void OilSlick::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("oilSlick"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setScale(0.2, 0.2);

	this->setPosition(Game::WINDOW_WIDTH / 2, 30);
	//randomize
	//this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("oilSlickSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);


	Collider* collide = new Collider("OilCollide", sprite, Collider::ObjectType::OilSlick);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);

}

void OilSlick::onRelease()
{
	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 65 - rand() % 65, 0);
}

void OilSlick::onActivate()
{
	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 65 - rand() % 65, 0);
}

ObjectPoolable* OilSlick::clone()
{
	ObjectPoolable* copyObj = new OilSlick(this->name);
	return copyObj;
}
