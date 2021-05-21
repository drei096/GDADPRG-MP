#include "EnemyCyanCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "EnemyCyanCar.h"

EnemyCyanCarClone::EnemyCyanCarClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* enemyCyanPool = new GameObjectPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG, new EnemyCyanCar("enemyCyan"), numEnemies, NULL);
	enemyCyanPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyCyanPool);
}

EnemyCyanCarClone::~EnemyCyanCarClone()
{
}

void EnemyCyanCarClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];

	if (inputController->isFirstGear() || inputController->isSecondGear())
	{
		GameObjectPool* enemyCyanPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			enemyCyanPool->requestPoolable();

		}
	}
}