#include "ShortTimeCollisions.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "PlayerCar.h"
#include "ApplicationManager.h"
#include "CarCrashScreen.h"
#include <iostream>

ShortTimeCollisions::ShortTimeCollisions(string name) : ObjectComponent(name, Script)
{
}

ShortTimeCollisions::~ShortTimeCollisions()
{
	ObjectComponent::~ObjectComponent();
}

void ShortTimeCollisions::perform()
{
	PlayerCar* player = (PlayerCar*)this->getOwner();

	if (player == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	if (player->speedCollision >= 1) {

		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks >= 1.5f && player->speedCollision < 3) {
			this->ticks = 0;
			player->speedCollision = 0;
		}
		else if (this->ticks >= 1.5f && player->speedCollision >= 3) {
			ApplicationManager::getInstance()->pauseApplication();
			CarCrashScreen* carCrashScreen = new CarCrashScreen("carCrashScreen");
			GameObjectManager::getInstance()->addObject(carCrashScreen);
		}
		else if (this->ticks < 1.5f && player->speedCollision >= 3) {
			ApplicationManager::getInstance()->pauseApplication();
			CarCrashScreen* carCrashScreen = new CarCrashScreen("carCrashScreen");
			GameObjectManager::getInstance()->addObject(carCrashScreen);
		}
	}

}
