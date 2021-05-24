#include "EnemyTruckClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "EnemyTruck.h"
#include "BGMovement.h"

EnemyTruckClone::EnemyTruckClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyTruckPool = new GameObjectPool(ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG, new EnemyTruck("enemyTruck"), numEnemies, NULL);
	enemyTruckPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyTruckPool);
}

EnemyTruckClone::~EnemyTruckClone()
{
}

void EnemyTruckClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (inputController->isFirstGear() || inputController->isSecondGear() && bgMove->totalDistanceTravelled > (bgMove->MAX_DISTANCE / 100) * 7)
	{
		GameObjectPool* enemyTruckPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			enemyTruckPool->requestPoolable();

		}
	}
}
