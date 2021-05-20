#include "OilSlickClone.h"
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
	GameObjectPool* oilSlickPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::OIL_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		oilSlickPool->requestPoolable();

	}
}
