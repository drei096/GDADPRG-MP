#pragma once
#include "GameObject.h"

class Collider;
class CollisionListener {

public:
	//add pure virtual functions here

	virtual ~CollisionListener() {}

	virtual void onCollide(Collider* object) = 0;
	virtual void onButtonReleased(Collider* object) = 0;

protected:
	CollisionListener() {}
};
