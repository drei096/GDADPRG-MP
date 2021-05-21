#include "FuelCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "FuelCar.h"

FuelCarClone::FuelCarClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyFuelPool = new GameObjectPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG, new FuelCar("enemyFuel"), numEnemies, NULL);
	enemyFuelPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyFuelPool);
}

FuelCarClone::~FuelCarClone()
{
}

void FuelCarClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];

	if (inputController->isFirstGear() || inputController->isSecondGear())
	{
		GameObjectPool* enemyFuelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			enemyFuelPool->requestPoolable();

		}
	}
}
