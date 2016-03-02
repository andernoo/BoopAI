#pragma once
#include "Food.h"
#include "NeuralNetwork.h"
#include <ctime>
#include <Box2D\Box2D.h>
#include "math_3d.h"
#include "Entity.h"

#define NUM_OUTPUTS 7
#define NUM_INPUTS 3
#define NUM_HIDDEN 1
#define NUM_PERHIDDEN 4
class Boop : public Entity {
public:
	std::vector<double> inputs;
	std::vector<double> outputs;
	b2Body* body=NULL;
	unsigned int foodEaten=0;
	NeuralNetwork *nn;
	float health=200;
	float survived=0;
	std::clock_t spawned;
	b2Vec3 colour = {0,0,0};
	bool m_markedForDeath = false;

	Boop();
	~Boop();

	void update();
	void eat(Food *food);
	void addBody(b2World *physWorld);
	void destroyBody(b2World *physWorld);
	Boop *reproduce(Boop *parent);
	void render();
	bool dead();
	int getEntityType();
	void contact(Entity * entity);
};