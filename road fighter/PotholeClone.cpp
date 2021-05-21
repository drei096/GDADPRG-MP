#include "PotholeClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "Pothole.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"

PotholeClone::PotholeClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* potholePool = new GameObjectPool(ObjectPoolHolder::POTHOLE_POOL_TAG, new Pothole("pothole"), numEnemies, NULL);
	potholePool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(potholePool);
}

PotholeClone::~PotholeClone()
{
}

void PotholeClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];

	if (inputController->isFirstGear() || inputController->isSecondGear())
	{
		GameObjectPool* potholePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POTHOLE_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			potholePool->requestPoolable();

		}
	}
}
