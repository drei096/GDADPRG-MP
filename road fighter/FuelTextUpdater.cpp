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
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];

	if (fuelScore == NULL || levelOverlay == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//cout << collisionCount << endl;
	//cout << carProgress->laps << endl;

	this->ticks += this->deltaTime.asSeconds() * 1.5;

	levelOverlay->fuel = 100 - this->ticks - player->collisions; //slowed down the decrease rate of fuel

	fuelScore->setText("FUEL \n" + (to_string)(levelOverlay->fuel));

	if (levelOverlay->fuel <= 10) {
		this->lowFuel += this->deltaTime.asSeconds();
		if (this->lowFuel >= 1.0f) {
			SFXManager::getInstance()->getSFX("beep")->play();
			this->lowFuel = 0;
		}
	}

	if (levelOverlay->fuel == 0) {
		ApplicationManager::getInstance()->pauseApplication();
		NoFuelScreen* noFuelScreen = new NoFuelScreen("noFuelScreen");
		GameObjectManager::getInstance()->addObject(noFuelScreen);
	}

	

}
