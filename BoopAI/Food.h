#pragma once
#include <vector>
#include "Entity.h"
#include "math_3d.h"
#include <iostream>

class Food : public Entity {
public:
	bool eaten = false;
	b2Body *body;
	Food(b2World *physWorld);
	~Food();

	int getEntityType();
};