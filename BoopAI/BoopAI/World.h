#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>
#include "ContactListener.h"

class World {
private:
	GLuint boopBuffer;
	GLuint foodBuffer;
	ContactListener contactListener;
public:
	std::vector<Boop*> boops;    // An arraylist for all the creatures
	std::vector<Food*> foods;
	b2World *physWorld;

	// Constructor
	World(b2World *physWorld, bool persist);

	// Make a new creature
	void newBoop(std::vector<double> weights);
	void newBoop();

	void newFood();

	// Run the world
	void run();
	void render();
};