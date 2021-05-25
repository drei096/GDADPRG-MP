#include <SFML/Audio.hpp>
#include <iostream>
#include <cstddef>
#include "SFXManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance() {
	//initialize only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}
	return sharedInstance;
}

void SFXManager::loadAllSFX() {
	//BGM LOADING
	loadSFX("menuBGM", "Media/Sounds/BGM/speedrun.wav");
	SFXManager::getInstance()->getSFX("menuBGM")->setLoop(true);
	loadSFX("levelBGM", "Media/Sounds/BGM/dubidubidapdap.wav");
	SFXManager::getInstance()->getSFX("levelBGM")->setLoop(true);
	loadSFX("gameOverBGM", "Media/Sounds/BGM/designate_patreon.ogg");
	SFXManager::getInstance()->getSFX("gameOverBGM")->setLoop(true);
	loadSFX("level_endBGM", "Media/Sounds/BGM/level_end.ogg");

	//SFX LOADING
	loadSFX("collide", "Media/Sounds/SFX/collide.ogg");
	loadSFX("explode", "Media/Sounds/SFX/explode.wav");
	loadSFX("glassbreak", "Media/Sounds/SFX/glass_break.wav");
	loadSFX("beep", "Media/Sounds/SFX/beep.ogg");
	loadSFX("coin", "Media/Sounds/SFX/coin1.wav");
	loadSFX("skid", "Media/Sounds/SFX/skid.wav");
	loadSFX("loss", "Media/Sounds/SFX/sadloss.wav");
	loadSFX("horn", "Media/Sounds/SFX/horn.wav");
}

void SFXManager::loadSFX(string key, string path) {
	SoundBuffer* SFX = new sf::SoundBuffer();
	SFX->loadFromFile(path);
	Sound* sound = new sf::Sound();
	sound->setBuffer(*SFX);
	SFXMap[key] = sound;
}

sf::Sound* SFXManager::getSFX(std::string key) {
	if (SFXMap[key] != NULL) {
		return SFXMap[key];
	}
	else {
		std::cout << "No SFX found for " << key;
		return NULL;
	}
}

void SFXManager::play(string key)
{
	SFXManager::getInstance()->getSFX(key)->play();
	SFXManager::getInstance()->setVolume(key, 50);
}

void SFXManager::setVolume(string key, int volume)
{
	SFXManager::getInstance()->getSFX(key)->setVolume(volume);
}
