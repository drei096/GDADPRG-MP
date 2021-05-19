#pragma once
#include "GameObjectPool.h"
#include <unordered_map>

typedef std::unordered_map<string, GameObjectPool*> PoolMap;

//class that holds N object pools for easier retrieval
class ObjectPoolHolder
{
public:
	//pool names
	static string ENEMY_CAR_POOL_TAG;
	static string BULLET_POOL_TAG;

	static ObjectPoolHolder* getInstance();

	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(string tag);

private:
	ObjectPoolHolder() {};
	ObjectPoolHolder(ObjectPoolHolder const&) {};             // copy constructor is private
	ObjectPoolHolder& operator=(ObjectPoolHolder const&) {};  // assignment operator is private
	static ObjectPoolHolder* sharedInstance;

	PoolMap poolMap;


};

