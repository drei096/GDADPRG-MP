#include "BGMovement.h"
#include "Game.h"
#include "GameObject.h"
#include "ApplicationManager.h"
BGMovement::BGMovement(string name) : ObjectComponent(name, Script)
{

}

BGMovement::~BGMovement()
{
	ObjectComponent::~ObjectComponent();
}

void BGMovement::perform()
{
	//make BG scroll slowly
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;
	this->getOwner()->getTransformable()->move(offset * deltaTime.asSeconds());


	sf::Vector2f localPos = this->getOwner()->getTransformable()->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		//this->getOwner()->getTransformable()->setPosition(0, -Game::WINDOW_HEIGHT * 7);
		ApplicationManager::getInstance()->pauseApplication();
	}

}