#include "EnemyCarClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar.h"

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
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();

	}
}