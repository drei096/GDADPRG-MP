#include "SpeedTextUpdater.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "CarProgressMovement.h"
#include "ProgressBar.h"
#include "UIText.h"
#include "LevelOverlay.h"
#include <iostream>
#include "PhysicsManager.h"
#include "PlayerCar.h"
#include "BGMovement.h"

SpeedTextUpdater::SpeedTextUpdater(string name) : ObjectComponent(name, Script)
{
}

SpeedTextUpdater::~SpeedTextUpdater()
{
	ObjectComponent::~ObjectComponent();
}

void SpeedTextUpdater::perform()
{
	UIText* textSpeed = (UIText*)GameObjectManager::getInstance()->findObjectByName("speed_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	ProgressBar* carProgress = (ProgressBar*)GameObjectManager::getInstance()->findObjectByName("progressBar");
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (textSpeed == NULL || levelOverlay == NULL || carProgress == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	levelOverlay->speed = bgMove->SPEED_MULTIPLIER / 2.5;
	textSpeed->setText("SPEED \n" + (to_string)(levelOverlay->speed) + " KM/H");

}
