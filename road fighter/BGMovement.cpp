#include "BGMovement.h"
#include "Game.h"
#include "GameObject.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "LevelOverScreen.h"
BGMovement::BGMovement(string name, float _MAX, int _level) : ObjectComponent(name, Script)
{
	this->MAX_DISTANCE = _MAX;
	this->level = _level;
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

float BGMovement::laneCheck()
{
	if (this->left == false && this->leftMost == false && this->right == false && this->rightMost == false) {
		return (65 / ((rand() % 2) + 1)) * (rand() % 2 > 0 ? -1 : 1);
	}
	else if (this->left == false && this->leftMost == false && this->right == true && this->rightMost == true) {
		return (65 / ((rand() % 2) + 1) * -1);
	}
	else if (this->left == true && this->leftMost == true && this->right == false && this->rightMost == false) {
		return (65 / ((rand() % 2) + 1));
	}
	else if (this->left == false && this->leftMost == true && this->right == true && this->rightMost == false) {
		return (65 * (rand() % 2 > 0 ? -1 : 1));
	}
	else if (this->left == true && this->leftMost == false && this->right == false && this->rightMost == true) {
		return (65 * (rand() % 2 > 0 ? -1 : 1));
	}
	else if (this->left == true && this->leftMost == false && this->right == true && this->rightMost == false) {
		return ((rand() % 2 > 0 ? -65 : 32.5));
	}
	else if (this->left == false && this->leftMost == true && this->right == false && this->rightMost == true) {
		return ((rand() % 2 > 0 ? 65 : -32.5));
	}
	else if (this->left == false && this->leftMost == true && this->right == true && this->rightMost == true) {
		return -65;
	}
	else if (this->left == true && this->leftMost == false && this->right == true && this->rightMost == true) {
		return -32.5;
	}
	else if (this->left == true && this->leftMost == true && this->right == false && this->rightMost == true) {
		return 32.5;
	}
	else if (this->left == true && this->leftMost == true && this->right == true && this->rightMost == false) {
		return 65;
	}
	else if (this->left == true && this->leftMost == false && this->right == false && this->rightMost == false) {
		float random = rand() % 2;
		if (random == 0) {
			return -32.5;
		}
		else {
			return (65 / ((rand() % 2) + 1));
		}
	}
	else if (this->left == false && this->leftMost == true && this->right == false && this->rightMost == false) {
		float random = rand() % 2;
		if (random == 0) {
			return -65;
		}
		else {
			return (65 / ((rand() % 2) + 1));
		}
	}
	else if (this->left == false && this->leftMost == false && this->right == true && this->rightMost == false) {
		float random = rand() % 2;
		if (random == 0) {
			return 65;
		}
		else {
			return (-65 / ((rand() % 2) + 1));
		}
	}
	else if (this->left == false && this->leftMost == false && this->right == false && this->rightMost == true) {
		float random = rand() % 2;
		if (random == 0) {
			return 32.5;
		}
		else {
			return (-65 / ((rand() % 2) + 1));
		}
	}
}
