#pragma once
#include "ObjectComponent.h"
class CarProgressMovement : public ObjectComponent
{
public:
	CarProgressMovement(string name);
	~CarProgressMovement();

	void perform();

	
private:
	int laps = 1;
	

};

