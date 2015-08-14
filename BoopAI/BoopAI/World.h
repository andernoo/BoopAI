#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>

class World {
private:
	int m_sizeOfGen;
public:
	std::vector<Boop*> boops;    // An arraylist for all the creatures
	std::vector<Boop*> deadBoops;    // An arraylist for all the creatures
	Food *food;

	// Constructor
	World(int num);

	// Make a new creature
	void born(float x, float y);

	// Run the world
	void run();
};