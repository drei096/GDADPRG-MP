#include "BG.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BGMovement.h"

BG::BG(std::string name, float _MAX) : GameObject(name) {
	this->MAX_DISTANCE = _MAX;
}

void BG::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("bg1"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	
	
	sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	getTransformable()->setPosition(100, -Game::WINDOW_HEIGHT * 8);
	
	BGMovement* movement = new BGMovement("BG_Movement", this->MAX_DISTANCE);
	this->attachComponent(movement);
	

	Renderer* renderer = new Renderer("BG");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
}