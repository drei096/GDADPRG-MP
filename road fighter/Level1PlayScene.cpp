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

Level1PlayScene::Level1PlayScene() : Scene(SceneManager::LEVEL1_SCENE_NAME)
{
}

Level1PlayScene::~Level1PlayScene()
{
}

void Level1PlayScene::onLoadResources()
{
	/*
	UIText* scoreText = new UIText("score_text");
	scoreText->setPosition(-70,-80);
	scoreText->setSize(10);
	scoreText->setText("1P\n 00000000");
	*/
	ApplicationManager::getInstance()->resumeApplication();
}

void Level1PlayScene::onLoadObjects()
{

	BG* bg = new BG("BG", 100000.0f);
	this->registerObject(bg);

	LevelOverlay* levelOverlay = new LevelOverlay("levelOverlay");
	this->registerObject(levelOverlay);

	ProgressBar* progress = new ProgressBar("progressBar");
	this->registerObject(progress);

	PlayerCar* player = new PlayerCar("player");
	this->registerObject(player);
	//GameObjectManager::getInstance()->addObject(player);


	srand(time(NULL));
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemyCarClone* swarmHandler = new EnemyCarClone(5, "SwarmHandler");
	enemiesManager->attachComponent(swarmHandler);
	this->registerObject(enemiesManager);

	
	EmptyGameObject* cyanEnemiesManager = new EmptyGameObject("cyanEnemiesManager");
	EnemyCyanCarClone* CSwarmHandler = new EnemyCyanCarClone(5, "CSwarmHandler");
	enemiesManager->attachComponent(CSwarmHandler);
	this->registerObject(cyanEnemiesManager);
	

	PhysicsManager::initialize("PlayerP6", player);
	PhysicsManager::initialize("EnemyCarP6", enemiesManager);
	//PhysicsManager::initialize("CyanEnemyCarP6", cyanEnemiesManager);
}

void Level1PlayScene::onUnloadObjects()
{
	PhysicsManager::getInstance()->clearAll();
	Scene::onUnloadObjects();
}

void Level1PlayScene::onUnloadResources()
{

}
