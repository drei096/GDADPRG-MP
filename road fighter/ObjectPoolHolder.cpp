#include "ObjectPoolHolder.h"

string ObjectPoolHolder::ENEMY_CAR_POOL_TAG = "EnemyCarPool";
string ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG = "EnemyCyanCarPool";
string ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG = "EnemyTruckPool";
string ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG = "EnemyYellowCarPool";
string ObjectPoolHolder::ENEMY_FUEL_POOL_TAG = "EnemyFuelCarPool";
string ObjectPoolHolder::POTHOLE_POOL_TAG = "PotholePool";

ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(string tag)
{
	return this->poolMap[tag];
}
