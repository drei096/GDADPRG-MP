#include "ScoreTextUpdater.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "CarProgressMovement.h"
#include "ProgressBar.h"
#include "UIText.h"
#include "LevelOverlay.h"
#include <iostream>
#include "PhysicsManager.h"
#include "PlayerCar.h"

ScoreTextUpdater::ScoreTextUpdater(string name) : ObjectComponent(name, Script)
{
}

ScoreTextUpdater::~ScoreTextUpdater()
{
	ObjectComponent::~ObjectComponent();
}

void ScoreTextUpdater::perform()
{
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");

	if (textScore == NULL || levelOverlay == NULL || player == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//for mula for computing score is passed car multiplied by 50 + bonus car taken multiplied by 1000
	levelOverlay->score = (player->passedCar * 50) + (player->bonus * 1000);

	//avoiding negative scoring
	if (levelOverlay->score <= 0)
		levelOverlay->score = 0;

	//text score update
	textScore->setText("SCORE\n" + (to_string)(levelOverlay->score));

}
