#include "BGMovement.h"
#include "Game.h"
#include "GameObject.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "LevelOverScreen.h"
BGMovement::BGMovement(string name, float _MAX) : ObjectComponent(name, Script)
{
	this->MAX_DISTANCE = _MAX;
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
	this->totalDistanceTravelled += offset.y * deltaTime.asSeconds();
	//cout << this->totalDistanceTravelled << endl;


	sf::Vector2f localPos = this->getOwner()->getTransformable()->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		this->getOwner()->getTransformable()->setPosition(100, -Game::WINDOW_HEIGHT * 8);
		//ApplicationManager::getInstance()->pauseApplication();
	}

	if (this->totalDistanceTravelled >= this->MAX_DISTANCE) {
		ApplicationManager::getInstance()->pauseApplication();
		LevelOverScreen* levelOverScreen = new LevelOverScreen("levelOverScreen");
		GameObjectManager::getInstance()->addObject(levelOverScreen);
	}
}