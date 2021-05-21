#pragma once
#include "ObjectComponent.h"
#include "CollisionListener.h"
#include "GameObject.h"
class Collider : public ObjectComponent {

public:
	enum ObjectType { Player = 0, Fuel = 1, EnemyCar = 2, None = 3 };

	Collider(string name, sf::Sprite* sprite, ObjectType type);

	ObjectType type = None;

	void setCollisionListener(CollisionListener* listener);

	void setChecked(bool flag);
	bool isChecked();

	bool willCollide(Collider* another);
	bool alreadyCollided();
	void setAlreadyCollided(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);
	void collisionEnter(GameObject* gameObjects);
	void collisionExit(GameObject* gameObjects);
	float ticks = 0;

	void perform();
private:
	bool collided = false;
	bool checked = false;
	sf::FloatRect localBounds;
	sf::Sprite* sprite;
	CollisionListener* listener;
};

