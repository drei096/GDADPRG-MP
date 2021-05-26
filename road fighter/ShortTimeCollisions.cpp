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

	//condition if speedcollision is 1
	if (player->speedCollision >= 1) {
		//timer starts when speedcollison is 1
		this->ticks += this->deltaTime.asSeconds();

		//if there are no 3 collisions within 1.5 seconds
		if (this->ticks >= 1.5f && player->speedCollision < 3) {
			//reset timer and speedcollisions
			this->ticks = 0;
			player->speedCollision = 0;
		}
		//if 3 collisions are recorded within 1.5 seconds then game over
		else if (this->ticks >= 1.5f && player->speedCollision >= 3) {
			ApplicationManager::getInstance()->pauseApplication();
			CarCrashScreen* carCrashScreen = new CarCrashScreen("carCrashScreen");
			GameObjectManager::getInstance()->addObject(carCrashScreen);
		}
		//if 3 collisions are recorded within 1.5 seconds then game over
		else if (this->ticks < 1.5f && player->speedCollision >= 3) {
			ApplicationManager::getInstance()->pauseApplication();
			CarCrashScreen* carCrashScreen = new CarCrashScreen("carCrashScreen");
			GameObjectManager::getInstance()->addObject(carCrashScreen);
		}
	}

}
