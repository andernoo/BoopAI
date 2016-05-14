#pragma once
#include <vector>
#include <ctime>
#include "NeuralNetwork.h"
#include <Box2D/Box2D.h>

#define NUM_INPUTS 4
#define NUM_OUTPUTS 7
#define NUM_HIDDEN 1
#define NUM_PER_HIDDEN 5
class Boop
{
	float health = 1000;
	std::clock_t spawned;
	std::vector<double> inputs, outputs;
	NeuralNetwork* nn = new NeuralNetwork(NUM_INPUTS, NUM_HIDDEN, NUM_OUTPUTS, NUM_PER_HIDDEN);
public:
	Boop(b2World * world, int id);
	~Boop();

	int id;
	b2Vec3 colour = { 0.1f, 0.1f, 0.1f };
	b2Body* body;
	void step();
};
