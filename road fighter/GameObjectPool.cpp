#include "GameObjectPool.h"
#include <iostream>
#include "GameObjectManager.h"

GameObjectPool::GameObjectPool(string tag, ObjectPoolable* poolableCopy, int poolableSize, GameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}

GameObjectPool::~GameObjectPool()
{
	this->objectCopy = NULL;
	this->parent = NULL;
}
//initializes the object pool
void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++) {
		ObjectPoolable* poolableObject = this->objectCopy->clone();
		//instantiate object but disable it.
		if (this->parent != NULL) {
			this->parent->attachChild(poolableObject);
		}
		else {
			GameObjectManager::getInstance()->addObject(poolableObject);
		}
		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}

ObjectPoolable* GameObjectPool::requestPoolable()
{
	if (this->hasObjectAvailable(1)) {
		ObjectPoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
		this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
		this->usedObjects.push_back(poolableObject);

		//std::cout << "Requested object. Available: " << this->availableObjects.size() << " Used: " << this->usedObjects.size() << "\n";
		this->setEnabled(poolableObject, true);
		return poolableObject;
	}
	else {
		//std::cout << " No more poolable " + this->objectCopy->getName() + " available! \n";
		return NULL;
	}
}

ObjectList GameObjectPool::requestPoolableBatch(int size)
{
	ObjectList returnList;
	if (this->hasObjectAvailable(size)) {
		for (int i = 0; i < size; i++) {
			returnList.push_back(this->requestPoolable());
		}
	}
	else {
		std::cout << "Insufficient " + this->objectCopy->getName() + " available in pool. Count is: " << this->availableObjects.size() <<
			" while requested is " << size << "!\n";
	}

	return returnList;
}

void GameObjectPool::releasePoolable(ObjectPoolable* poolableObject)
{
	//find object in used
	int index = -1;
	for (int i = 0; i < this->usedObjects.size(); i++) {
		if (this->usedObjects[i] == poolableObject) {
			index = i;
			break;
		}
	}
	//std::cout << "Poolable index in used: " << index << "\n";
	if (index > -1) {
		this->usedObjects.erase(this->usedObjects.begin() + index);
		this->availableObjects.push_back(poolableObject);
		this->setEnabled(poolableObject, false);
	}

}

void GameObjectPool::releasePoolableBatch(ObjectList objectList)
{
	for (int i = 0; i < objectList.size(); i++) {
		this->releasePoolable(objectList[i]);
	}
}

void GameObjectPool::removeFromPool(ObjectPoolable* poolableObject)
{
	int index = -1;
	for (int i = 0; i < this->usedObjects.size(); i++) {
		if (this->usedObjects[i] == poolableObject) {
			index = i;
			break;
		}
	}

	if (index > -1) {
		cout << "Used" << endl;
		this->usedObjects.erase(this->usedObjects.begin() + index);
	}

	if (index == -1) {
		for (int i = 0; i < this->availableObjects.size(); i++) {
			if (this->availableObjects[i] == poolableObject) {
				index = i;
				break;
			}
		}

		if (index > -1) {
			cout << "Available" << endl;
			this->availableObjects.erase(this->availableObjects.begin() + index);
		}
	}

	this->setEnabled(poolableObject, false);
}

string GameObjectPool::getTag()
{
	return this->tag;
}

void GameObjectPool::setEnabled(ObjectPoolable* poolableObject, bool flag)
{
	if (flag) {
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}
	else {
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}