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


	if (fuelScore == NULL || levelOverlay == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//cout << collisionCount << endl;
	//cout << carProgress->laps << endl;

	this->ticks += this->deltaTime.asSeconds() * 1.5;

	levelOverlay->fuel = 100 - (int)this->ticks;

	fuelScore->setText("FUEL\n\t\t" + (to_string)(levelOverlay->fuel));

	if (levelOverlay->fuel == 0) {
		ApplicationManager::getInstance()->pauseApplication();
	}

}
