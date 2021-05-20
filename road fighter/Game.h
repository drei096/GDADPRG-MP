#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "TextureManager.h"

using namespace std;
using namespace sf;

class Game
{
public:
	static const int WINDOW_HEIGHT = 600;
	static const int WINDOW_WIDTH = 750;
	const Time timePerFrame = seconds(1.0f / 60.0f);

public:
	Game();
	void run();
	//void onClick();
	//void onReleaseClick();

private:
	RenderWindow window;
	//vector<Entity*> entityList;

private:
	void processEvents();
	void update(Time);
	void render();
};

