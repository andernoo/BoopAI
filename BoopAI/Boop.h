#pragma once
#include "Food.h"
#include "NeuralNetwork.h"
#include <ctime>
#include <Box2D\Box2D.h>
#include "math_3d.h"
#include "Entity.h"

class Boop : public Entity {
public:
	std::vector<double> inputs;
	b2World *physWorld;
	b2Body* body=NULL;
	unsigned int foodEaten=0;
	NeuralNetwork nn;
	float health=200;
	float survived;
	std::clock_t spawned=std::clock();
	b2Vec3 colour = {0,0,0};

	// Create a "boop" creature
	Boop(b2World *physWorld);

	~Boop();

	void update();
	void eat(Food *food);
	void addBody();
	void destroyBody();

	// At any moment there is a teeny, tiny chance a boop will reproduce
	Boop *reproduce(Boop *parent);

	// Method to display
	void render();

	int getEntityType();

	// Death
	bool dead();
};