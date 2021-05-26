#include "FuelTextUpdater.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "CarProgressMovement.h"
#include "ProgressBar.h"
#include "UIText.h"
#include "LevelOverlay.h"
#include "ApplicationManager.h"
#include <iostream>
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "NoFuelScreen.h"
#include "SFXManager.h"
#include "PhysicsManager.h"

FuelTextUpdater::FuelTextUpdater(string name) : ObjectComponent(name, Script)
{
}

FuelTextUpdater::~FuelTextUpdater()
{
	ObjectComponent::~ObjectComponent();
}

void FuelTextUpdater::perform()
{
	UIText* fuelScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("fuel_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");

	if (fuelScore == NULL || levelOverlay == NULL || player == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//fuel decrease is equal to 1.5 per 1 second
	this->ticks += this->deltaTime.asSeconds() * 1.5;

	//formula for computing fuel which is the current fuel value + the bonuses acquired by the player multiplied by 10 - time passed - number of collisions
	levelOverlay->fuel = currfuel + (player->bonus * 10) - this->ticks - player->collisions;

	//to avoid overflowing of fuel
	if (levelOverlay->fuel >= 100)
		levelOverlay->fuel = 100;

	//text setter
	fuelScore->setText("FUEL \n" + (to_string)(levelOverlay->fuel));

	//sound cue for low fuel
	if (levelOverlay->fuel <= 10) {
		this->lowFuel += this->deltaTime.asSeconds();
		if (this->lowFuel >= 1.0f) {
			SFXManager::getInstance()->getSFX("beep")->play();
			this->lowFuel = 0;
		}
	}

	//if fuel reaches zero
	if (levelOverlay->fuel == 0) {
		ApplicationManager::getInstance()->pauseApplication();
		NoFuelScreen* noFuelScreen = new NoFuelScreen("noFuelScreen");
		GameObjectManager::getInstance()->addObject(noFuelScreen);
	}

	player->isCollidedFuel = false;

}
