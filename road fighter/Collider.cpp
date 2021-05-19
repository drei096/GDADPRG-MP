#include "Collider.h"
#include <iostream>

Collider::Collider(string name, sf::Sprite* sprite, ObjectType type) : ObjectComponent(name, Script)
{
    this->sprite = sprite;
    this->type = type;
}

void Collider::setCollisionListener(CollisionListener* listener)
{
    this->listener = listener;
}

void Collider::setChecked(bool flag)
{
    this->checked = flag;
}

bool Collider::isChecked()
{
    return this->checked;
}

bool Collider::willCollide(Collider* another)
{
    if (this->getGlobalBounds().intersects(another->getGlobalBounds())) {
        setAlreadyCollided(true);
        return true;
    }
    return false;
}

bool Collider::alreadyCollided()
{
    return this->collided;
}

void Collider::setAlreadyCollided(bool flag)
{
    this->collided = flag;
}

sf::FloatRect Collider::getGlobalBounds()
{
    sf::FloatRect bounds = this->sprite->getGlobalBounds();
    bounds = this->owner->getGlobalTransform().transformRect(bounds);
    return bounds;
}

void Collider::setLocalBounds(sf::FloatRect localBounds)
{
    this->localBounds = localBounds;
}

void Collider::collisionEnter(GameObject* gameObjects)
{

}

void Collider::collisionExit(GameObject* gameObjects)
{

}

void Collider::perform()
{

}
