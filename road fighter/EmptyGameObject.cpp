#include "EmptyGameObject.h"

EmptyGameObject::EmptyGameObject(string name) : GameObject(name)
{

}

EmptyGameObject::~EmptyGameObject()
{
	GameObject::~GameObject();
}

void EmptyGameObject::initialize()
{
}
