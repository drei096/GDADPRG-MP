#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject;

class ObjectComponent
{
public:
	enum componentType {NotSet = -1, Script = 0, Renderer = 1, Input = 2};
	ObjectComponent(string name, componentType type);
	virtual ~ObjectComponent();

	void attachOwner(GameObject* owner);
	void detachOwner();
	GameObject* getOwner();
	componentType getType();
	string getName();

	void setDeltaTime(Time deltaTime);
	virtual void perform() = 0;

protected:
	GameObject* owner;
	componentType type;
	string name;
	Time deltaTime;
};

