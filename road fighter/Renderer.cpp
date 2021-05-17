#include "Renderer.h"

Renderer::Renderer(string name) : ObjectComponent(name, ObjectComponent::Renderer)
{
	this->type = ObjectComponent::Renderer;
	this->renderStates = RenderStates::Default;
}

Renderer::~Renderer()
{
	delete this->drawable;
	ObjectComponent::~ObjectComponent();
}

void Renderer::assignTargetWindow(RenderWindow* window)
{
	this->targetWindow = window;
}

void Renderer::assignDrawable(Drawable* drawable)
{
	this->drawable = drawable;
}

void Renderer::setRenderStates(RenderStates renderStates)
{
	this->renderStates = renderStates;
}

void Renderer::perform()
{
	this->targetWindow->draw(*this->drawable, this->renderStates);
}

