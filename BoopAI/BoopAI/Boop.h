#pragma once
#include "Food.h"
#include "NeuralNetwork.h"
#include <ctime>
#include <Box2D\Box2D.h>
#include "math_3d.h"
#include "Entity.h"

class Boop : public Entity {
public:
	GLuint vao = 0;
	b2World *physWorld;
	b2Body* body;
	unsigned int foodEaten=0;
	NeuralNetwork nn;
	float health=200;
	float survived;
	std::clock_t spawned=std::clock();
	b2Vec3 colour = {0,0,0};

	// Create a "boop" creature
	Boop(b2World *physWorld, b2Vec2 l);

	~Boop();

	// A boop can find food and eat it
	void eat(Food *food);

	// At any moment there is a teeny, tiny chance a boop will reproduce
	Boop *reproduce(Boop *parent);

	// Method to update location
	void update(vector<Food*> food);

	// Method to display
	void render(GLuint boopBuffer);

	int getEntityType();

	// Death
	bool dead();
};