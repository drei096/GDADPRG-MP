#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

class TextureManager
{
public:
	static TextureManager* getInstance();
	void loadAllTextures();
	Texture* getTextureByKey(string);

private:
	TextureManager() {};
	TextureManager(TextureManager const&) {};
	static TextureManager* sharedInstance;
	
private:
	void loadTexture(string, string);
	unordered_map<string, Texture*> textureMap;
};

