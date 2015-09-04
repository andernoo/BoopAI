#pragma once
#include "DNA.h"
#include "Point.h"
#include "Food.h"
#include "NeuralNetwork.h"
#include <ctime>
#include <Box2D\Box2D.h>
#include "math_3d.h"

class Boop {
public:
	b2World *physWorld;
	// Define the dynamic body. We set its position and call the body factory.
	b2Body* body;
	int foodEaten;
	NeuralNetwork nn;
	Point *location; // Location
	b2Vec2 target;
	DNA *dna;          // DNA
	float health;     // Life timer
	// DNA will determine size and maxspeed
	float r;
	float maxspeed;
	float survived;
	std::clock_t spawned;

	// Create a "boop" creature
	Boop(b2World *physWorld, Point *l, DNA *dna_);

	void run(Food *f, GLuint boopBuffer);

	// A boop can find food and eat it
	void eat(Food *f);

	// At any moment there is a teeny, tiny chance a boop will reproduce
	Boop *reproduce(Boop *parent);

	// Method to update location
	void update(Food *f);

	// Wraparound
	void borders();

	// Method to display
	void display(GLuint boopBuffer);

	// Death
	bool dead();
};