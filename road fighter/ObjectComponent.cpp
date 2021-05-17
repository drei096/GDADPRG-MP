#include "ObjectComponent.h"

ObjectComponent::ObjectComponent(string name, componentType type)
{
	this->name = name;
	this->owner = NULL;
	this->type = type;
}

ObjectComponent::~ObjectComponent()
{
	this->owner = NULL;
	this->type = NotSet;
}

void ObjectComponent::attachOwner(GameObject* owner)
{
	this->owner = owner;
}

void ObjectComponent::detachOwner()
{
	delete this;
}

GameObject* ObjectComponent::getOwner()
{
	return this->owner;
}

ObjectComponent::componentType ObjectComponent::getType()
{
	return this->type;
}

string ObjectComponent::getName()
{
	return this->name;
}

void ObjectComponent::setDeltaTime(Time deltaTime)
{
	this->deltaTime = deltaTime;
}
