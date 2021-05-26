#include "CarProgressMovement.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "BGMovement.h"
#include "PlayerCar.h"
#include "ProgressBar.h"
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
	ProgressBar* progress = (ProgressBar*)this->getOwner()->getParent();

	if (playerTransformable == NULL || bgMove == NULL || progress == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//update progress car number of laps by the component's laps count
	progress->laps = this->laps;
	/*
	* formula for calculating the distance travalled from a certain point to another point
	* basically a percentage scale
	* EXAMPLE:
	* totalDistanceTravalled is 900
	* MAX_DISTANCE is 100000
	* laps is 1
	* totalDistance = 900 - (100000 / 100) * 1
	* totalDistance = -100
	* This will not trigger the if condition which is totalDistance is greater than or equal to 0
	*/
	float totalDistance = bgMove->totalDistanceTravelled - (bgMove->MAX_DISTANCE / 100) * this->laps;

	//moves car by -5 x value and adds to laps when totalDistance reaches 0 or greater than 0
	if (totalDistance >= 0) {
		playerTransformable->move(-5,0);
		this->laps++;
	}

}
