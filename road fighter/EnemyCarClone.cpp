#include "EnemyCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "BGMovement.h"

EnemyCarClone::EnemyCarClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG, new EnemyCar("enemy"), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
}

EnemyCarClone::~EnemyCarClone()
{

}

void EnemyCarClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (inputController->isSecondGear() && bgMove->totalDistanceTravelled > bgMove->MAX_DISTANCE / 100)
	{
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			enemyPool->requestPoolable();
		}
	}
	
}