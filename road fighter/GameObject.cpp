#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
}

GameObject::~GameObject()
{
	for (int i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}

	for (int i = 0; i < this->componentList.size(); i++)
	{
		delete this->componentList[i];
	}

	this->childList.clear();
	this->childList.shrink_to_fit();
	this->componentList.clear();
	this->componentList.shrink_to_fit();

	if (this->parent != NULL)
	{
		this->parent = NULL;
	}
}

void GameObject::processInput(Event event)
{
	vector<ObjectComponent*> componentList = this->getComponentsOfType(ObjectComponent::componentType::Input);
	for (int j = 0; j < componentList.size(); j++) 
	{
		InputController* inputController = (InputController*)componentList[j];
		inputController->assignEvent(event);
		inputController->perform();
	}
	for (int i = 0; i < this->childList.size(); i++) 
	{
		this->childList[i]->processInput(event);
	}
}

void GameObject::update(Time deltaTime)
{
	vector<ObjectComponent*> componentList = this->getComponentsOfType(ObjectComponent::componentType::Script);

	for (int j = 0; j < componentList.size(); j++) 
	{
		componentList[j]->setDeltaTime(deltaTime);
		componentList[j]->perform();
	}

	for (int i = 0; i < this->childList.size(); i++) 
	{
		childList[i]->update(deltaTime);
	}
}

void GameObject::draw(RenderWindow* targetWindow, RenderStates renderStates)
{
	vector<ObjectComponent*> componentList = this->getComponentsOfType(ObjectComponent::componentType::Renderer);

	renderStates.transform = renderStates.transform * this->transformable.getTransform();

	for (int j = 0; j < componentList.size(); j++) 
	{
	
		Renderer* renderer = (Renderer*)componentList[j];
		renderer->assignTargetWindow(targetWindow);
		renderer->setRenderStates(renderStates);
		renderer->perform();
		
	}
	for (int i = 0; i < this->childList.size(); i++) 
	{
		this->childList[i]->draw(targetWindow, renderStates);
	}
}

string GameObject::getName()
{
	return name;
}

void GameObject::attachChild(GameObject* child)
{
	this->childList.push_back(child);
	child->parent = this;
	child->initialize(); //initialize when attaching to child
}

void GameObject::detachChild(GameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) 
	{
		if (this->childList[i] == child) 
		{
			index = i;
		}
	}

	if (index != -1) 
	{
		this->childList.erase(this->childList.begin() + index);
	}
}

void GameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}

void GameObject::attachComponent(ObjectComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void GameObject::detachComponent(ObjectComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i] == component) 
		{
			index = i;
			this->componentList[i]->detachOwner();
			break;
		}
	}

	if (index != -1) 
	{
		this->componentList.erase(this->componentList.begin() + index);
	}
}

ObjectComponent* GameObject::findComponentByName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getName() == name) 
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

ObjectComponent* GameObject::findComponentByType(ObjectComponent::componentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) 
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

vector<ObjectComponent*> GameObject::getComponentsOfType(ObjectComponent::componentType type)
{
	vector<ObjectComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getType() == type) 
		{
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

vector<ObjectComponent*> GameObject::getComponentsOfTypeRecursive(ObjectComponent::componentType type)
{
	vector<ObjectComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getType() == type) 
		{
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < this->childList.size(); i++) 
	{
		foundList = this->getComponentsRecursiveProper(this->childList[i], type, foundList);
	}

	return foundList;
}

Transformable* GameObject::getTransformable()
{
	return &this->transformable;
}

sf::FloatRect GameObject::getLocalBounds() {
	throw "getLocalBounds() not yet implemented!";
}

sf::FloatRect GameObject::getGlobalBounds() {
	throw "gtLocalBounds() not implemented!";
}

sf::Transform GameObject::getGlobalTransform() {
	GameObject* parentObj = this;
	vector<GameObject*> parentList;
	while (parentObj != NULL) {
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--) {
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}
	return transform;
}

GameObject* GameObject::getParent()
{
	return this->parent;
}

vector<ObjectComponent*> GameObject::getComponentsRecursiveProper(GameObject* object, ObjectComponent::componentType type, vector<ObjectComponent*> foundList)
{
	vector<GameObject*> children = object->childList;

	for (int i = 0; i < object->componentList.size(); i++) 
	{
		if (object->componentList[i]->getType() == type) 
		{
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < children.size(); i++) 
	{
		this->getComponentsRecursiveProper(children[i], type, foundList);
	}

	return foundList;
}

void GameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

bool GameObject::isEnabled()
{
	return this->enabled;
}
