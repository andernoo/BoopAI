#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>

class World {
private:
	GLuint boopBuffer;
public:
	std::vector<Boop*> boops;    // An arraylist for all the creatures
	std::vector<Boop*> deadBoops;    // An arraylist for all the creatures
	Food *food;
	b2World *physWorld;

	// Constructor
	World(b2World *physWorld, bool persist);

	// Make a new creature
	void newBoop(std::vector<double> weights);
	void newBoop();

	// Run the world
	void run();
};