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

private:
    SFXManager() {};
    SFXManager(SFXManager const&) {};
    SFXManager& operator=(SFXManager const&) {};
    static SFXManager* sharedInstance;

private:
    void loadSFX(string, string);
    std::unordered_map<string, Sound*> SFXMap;
};

