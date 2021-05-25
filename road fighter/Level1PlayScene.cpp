#include "Level1PlayScene.h"
#include "PlayerCar.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "UIText.h"
#include "Renderer.h"
#include "BG.h"
#include "EnemyCarClone.h"
#include "EmptyGameObject.h"
#include "PhysicsManager.h"
#include "ProgressBar.h"
#include "LevelOverlay.h"
#include "ApplicationManager.h"
#include "EnemyCar.h"
#include "EnemyBehavior.h"
#include "EnemyCyanCar.h"
#include "EnemyCyanCarClone.h"
#include "EnemyYellowCar.h"
#include "EnemyYellowCarClone.h"
#include "EnemyTruck.h"
#include "EnemyTruckClone.h"
#include "FuelCar.h"
#include "FuelCarClone.h"
#include "Pothole.h"
#include "PotholeClone.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "OilSlick.h"
#include "OilSlickClone.h"

Level1PlayScene::Level1PlayScene() : Scene(SceneManager::LEVEL1_SCENE_NAME)
{
}

Level1PlayScene::~Level1PlayScene()
{
}

void Level1PlayScene::onLoadResources()
{
	ApplicationManager::getInstance()->resumeApplication();
}

void Level1PlayScene::onLoadObjects()
{

	BG* bg = new BG("BG", 70000.0f, "bg1", 1);
	this->registerObject(bg);

	LevelOverlay* levelOverlay = new LevelOverlay("levelOverlay");
	this->registerObject(levelOverlay);

	ProgressBar* progress = new ProgressBar("progressBar");
	this->registerObject(progress);

	srand(time(NULL));
	

	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemyCarClone* swarmHandler = new EnemyCarClone(10, "SwarmHandler");
	enemiesManager->attachComponent(swarmHandler);
	this->registerObject(enemiesManager);

	EmptyGameObject* cyanEnemiesManager = new EmptyGameObject("cyanEnemiesManager");
	EnemyCyanCarClone* CSwarmHandler = new EnemyCyanCarClone(10, "CSwarmHandler");
	cyanEnemiesManager->attachComponent(CSwarmHandler);
	this->registerObject(cyanEnemiesManager);
	
	EmptyGameObject* yellowEnemiesManager = new EmptyGameObject("yellowEnemiesManager");
	EnemyYellowCarClone* YSwarmHandler = new EnemyYellowCarClone(10, "YSwarmHandler");
	yellowEnemiesManager->attachComponent(YSwarmHandler);
	this->registerObject(yellowEnemiesManager);

	EmptyGameObject* truckEnemiesManager = new EmptyGameObject("truckEnemiesManager");
	EnemyTruckClone* TSwarmHandler = new EnemyTruckClone(10, "TSwarmHandler");
	truckEnemiesManager->attachComponent(TSwarmHandler);
	this->registerObject(truckEnemiesManager);

	PlayerCar* player = new PlayerCar("player", 0);
	this->registerObject(player);

	EmptyGameObject* fuelEnemiesManager = new EmptyGameObject("fuelEnemiesManager");
	FuelCarClone* FSwarmHandler = new FuelCarClone(10, "FSwarmHandler");
	fuelEnemiesManager->attachComponent(FSwarmHandler);
	this->registerObject(fuelEnemiesManager);

	EmptyGameObject* potholeManager = new EmptyGameObject("potholeManager");
	PotholeClone* PSwarmHandler = new PotholeClone(10, "PSwarmHandler");
	potholeManager->attachComponent(PSwarmHandler);
	this->registerObject(potholeManager);

	EmptyGameObject* oilManager = new EmptyGameObject("oilManager");
	OilSlickClone* OSwarmHandler = new OilSlickClone(10, "PSwarmHandler");
	oilManager->attachComponent(OSwarmHandler);
	this->registerObject(oilManager);
	

	PhysicsManager::initialize("PlayerP6", player);
}

void Level1PlayScene::onUnloadObjects()
{
	PhysicsManager::getInstance()->clearAll();
	Scene::onUnloadObjects();
}

void Level1PlayScene::onUnloadResources()
{

}
