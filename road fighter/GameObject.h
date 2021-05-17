#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Renderer.h"
#include "ObjectComponent.h"
#include "InputController.h"

using namespace std;
using namespace sf;

class GameObject
{
public:
	GameObject(string);
	virtual ~GameObject();

	virtual void initialize() = 0;
	virtual void processInput(Event event);
	virtual void update(Time deltaTime);
	void draw(RenderWindow* targetWindow, RenderStates renderStates);

	string getName();

	void attachChild(GameObject* child);
	void detachChild(GameObject* child);
	void setPosition(float x, float y);

	void attachComponent(ObjectComponent* component);
	void detachComponent(ObjectComponent* component);
	ObjectComponent* findComponentByName(string name);
	ObjectComponent* findComponentByType(ObjectComponent::componentType type, string name);
	vector <ObjectComponent*> getComponentsOfType(ObjectComponent::componentType type);
	vector <ObjectComponent*> getComponentsOfTypeRecursive(ObjectComponent::componentType type);

	Transformable* getTransformable();
	GameObject* getParent();

protected:
	Transformable transformable;
	string name;
	vector<GameObject*> childList;
	vector<ObjectComponent*> componentList;
	GameObject* parent;

private:
	vector <ObjectComponent*> getComponentsRecursiveProper(GameObject* object, ObjectComponent::componentType type, vector<ObjectComponent*> foundList);


};

