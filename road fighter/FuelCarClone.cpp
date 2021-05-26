#include "FuelCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "FuelCar.h"
#include "BGMovement.h"

FuelCarClone::FuelCarClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyYellowPool = new GameObjectPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG, new FuelCar("enemyFuel"), numEnemies, NULL);
	enemyYellowPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyYellowPool);
}

FuelCarClone::~FuelCarClone()
{
}

void FuelCarClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	//first to appear in the map but spawn interval is long so it still might take a while for it to spawn and instantiated only when player is moving
	if (inputController->isSecondGear() && bgMove->totalDistanceTravelled > (bgMove->MAX_DISTANCE / 100))
	{
		GameObjectPool* fuelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			fuelPool->requestPoolable();

		}
	}
}
