#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

class SFXManager
{
public:
    static SFXManager* getInstance();
    void loadAllSFX();
    Sound* getSFX(string);

    void play(string key);
    void setVolume(string key, int volume);

    void deleteAllSFX();

private:
    SFXManager() {};
    SFXManager(SFXManager const&) {};
    SFXManager& operator=(SFXManager const&) {};
    static SFXManager* sharedInstance;

private:
    void loadSFX(string, string);
    std::unordered_map<string, Sound*> SFXMap;
};

