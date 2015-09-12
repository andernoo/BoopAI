#pragma once
#include <vector>
#include <Box2D\Box2D.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Entity.h"
// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// Evolution EcoSystem

// A collection of food in the world

class Food : public Entity {
public:
	b2Body *body;
	b2World *physWorld;
	std::vector<Food*> *foods;
	Food(b2World *physWorld, std::vector<Food*>*food);
	~Food();

	int getEntityType();
	void render(GLuint foodBuffer);
};