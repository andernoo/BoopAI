#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>
#include "Tournament.h"
#include <Box2D\Box2D.h>

#define NUM_PER_TOURNAMENT 8
#define NUM_TOURNAMENTS 10

class World {
private:
	void resetTournaments();
public:
	unsigned int generations = 0;
	std::vector<Boop*> deadBoops;
	std::vector<Tournament*> tournaments;

	// Constructor
	World(bool persist);

	// Run the world
	void run();
	void render();
	void writeToFile(std::vector<Boop*> boops);
};