#include "EnemyYellowCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "EnemyYellowCar.h"
#include "BGMovement.h"

EnemyYellowCarClone::EnemyYellowCarClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyYellowPool = new GameObjectPool(ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG, new EnemyYellowCar("enemyYellow"), numEnemies, NULL);
	enemyYellowPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyYellowPool);
}

EnemyYellowCarClone::~EnemyYellowCarClone()
{
}

void EnemyYellowCarClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (inputController->isSecondGear() && bgMove->totalDistanceTravelled > (bgMove->MAX_DISTANCE / 100) * 15)
	{
		GameObjectPool* enemyYellowPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			enemyYellowPool->requestPoolable();

		}
	}
}
