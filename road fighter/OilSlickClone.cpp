#include "OilSlickClone.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "BGMovement.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "OilSlick.h"

OilSlickClone::OilSlickClone(int numEnemies, string name) : ObjectComponent(name, Script)
{
	GameObjectPool* oilSlickPool = new GameObjectPool(ObjectPoolHolder::OIL_POOL_TAG, new OilSlick("oil"), numEnemies, NULL);
	oilSlickPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(oilSlickPool);
}

OilSlickClone::~OilSlickClone()
{
}

void OilSlickClone::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");

	if (inputController->isSecondGear() && bgMove->totalDistanceTravelled > (bgMove->MAX_DISTANCE / 100) * 10)
	{
		GameObjectPool* oilPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::OIL_POOL_TAG);
		this->ticks += this->deltaTime.asSeconds();

		if (this->ticks > SPAWN_INTERVAL) {
			this->ticks = 0.0f;
			oilPool->requestPoolable();

		}
	}
}
