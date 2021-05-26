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
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (textSpeed == NULL || levelOverlay == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//formula for getting speed is current multiplier of bg move divided by 2.5
	levelOverlay->speed = bgMove->SPEED_MULTIPLIER / 2.5;

	//speed text update
	textSpeed->setText("SPEED \n" + (to_string)(levelOverlay->speed) + " KM/H");

}
