#include "CarProgressMovement.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "BGMovement.h"
#include "PlayerCar.h"
#include <iostream>

CarProgressMovement::CarProgressMovement(string name) : ObjectComponent(name, Script)
{
}

CarProgressMovement::~CarProgressMovement()
{
	ObjectComponent::~ObjectComponent();
}

void CarProgressMovement::perform()
{
	Transformable* playerTransformable = this->getOwner()->getTransformable();
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (playerTransformable == NULL || bgMove == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}


	float totalDistance = bgMove->totalDistanceTravelled - (bgMove->MAX_DISTANCE / 100) * laps;


	cout << laps << endl;

	if (totalDistance >= 0) {
		playerTransformable->move(-5,0);
		laps++;
	}

}
