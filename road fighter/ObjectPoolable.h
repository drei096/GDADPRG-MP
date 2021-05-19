#pragma once
#include "GameObject.h"
class ObjectPoolable : public GameObject
{
public:
	ObjectPoolable(string name);
	//initializes the property of this object.
	virtual void initialize() = 0;

	//throws this event when this object has been released back to the pool.
	virtual void onRelease() = 0;

	//throws this event when this object has been activated from the pool.
	virtual void onActivate() = 0;

	//provides a copy of the poolable instance. must be implemented per specific class
	virtual ObjectPoolable* clone() = 0;
};

