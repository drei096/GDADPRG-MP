#pragma once
#include "ObjectComponent.h"
using namespace std;

class Renderer : public ObjectComponent
{
public:
	Renderer(string name);
	~Renderer();
	void assignTargetWindow(RenderWindow* window);
	void assignDrawable(Drawable* drawable);
	void setRenderStates(RenderStates renderStates);

	void perform();

private:
	RenderWindow* targetWindow;
	Drawable* drawable;
	RenderStates renderStates;
};

