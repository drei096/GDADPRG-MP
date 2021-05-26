#pragma once
#include "ObjectPoolable.h"
#include <vector>
#include <queue>

typedef std::vector<ObjectPoolable*> ObjectList;
class GameObjectPool
{
public:
	GameObjectPool(string tag, ObjectPoolable* poolableCopy, int poolableSize, GameObject* parent);
	~GameObjectPool();
	void initialize();
	bool hasObjectAvailable(int requestSize);
	ObjectPoolable* requestPoolable();
	ObjectList requestPoolableBatch(int size);

	void releasePoolable(ObjectPoolable* poolableObject);
	void releasePoolableBatch(ObjectList objectList);

	string getTag();

	ObjectList availableObjects;
	ObjectList usedObjects;

private:
	string tag;
	ObjectPoolable* objectCopy = NULL;
	GameObject* parent = NULL;
	int maxPoolSize = 20; //default;

	void setEnabled(ObjectPoolable* poolableObject, bool flag);
};

