#pragma once
#include <vector>
#include <Box2D\Box2D.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Entity.h"
#include <iostream>

class Food : public Entity {
public:
	bool eaten = false;
	b2Body *body;
	b2World *physWorld;
	std::vector<Food*> *foods;
	Food(b2World *physWorld, std::vector<Food*>*food);
	~Food();

	int getEntityType();
	void render(GLuint foodBuffer);
};