#pragma once
#include <SFML/System.hpp>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include "GameObject.h"

using namespace std;
using namespace sf;

typedef unordered_map<string, GameObject*> HashTable;
typedef vector<GameObject*> List;

class GameObjectManager : sf::NonCopyable
{
public:
    static GameObjectManager* getInstance();

    GameObject* findObjectByName(std::string name);
    List getAllObjects();
    int activeObjects();

    void processInput(Event event);
    void update(Time deltaTime);
    void draw(sf::RenderWindow* window);

    void addObject(GameObject* gameObject);
    void deleteObject(GameObject* gameObject);
    void deleteObjectByName(string name);
    void deleteAllObjectsInScene();

private:
    GameObjectManager() {};
    static GameObjectManager* sharedInstance;

    HashTable gameObjectMap;
    List gameObjectList;
};

