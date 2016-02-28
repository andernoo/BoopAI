#pragma once
#include "Food.h"
#include "NeuralNetwork.h"
#include <ctime>
#include <Box2D\Box2D.h>
#include "math_3d.h"
#include "Entity.h"
#define NUM_OUTPUTS 5
#define NUM_INPUTS 3
class Boop : public Entity {
public:
	std::vector<double> inputs;
	std::vector<double> outputs;
	b2Body* body=NULL;
	unsigned int foodEaten=0;
	neuralNetwork *nn;
	float health=200;
	float survived;
	std::clock_t spawned;
	b2Vec3 colour = {0,0,0};

	bool m_markedForDeath = false;

	// Create a "boop" creature
	Boop();

	~Boop();

	void update();
	void eat(Food *food);
	void addBody(b2World *physWorld);
	void destroyBody(b2World *physWorld);

	// At any moment there is a teeny, tiny chance a boop will reproduce
	Boop *reproduce(Boop *parent);

	// Method to display
	void render();

	// Death
	bool dead();
	int getEntityType();
	void contact(Entity * entity);
};