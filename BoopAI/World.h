#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>
#include "ContactListener.h"
#include <Box2D\Box2D.h>

#define NUM_PER_TOURNAMENT 8
#define NUM_TOURNAMENTS 10

class World {
private:
	GLuint foodBuffer;
	ContactListener contactListener;
	b2Body *groundBody;
	void resetTournaments();
public:
	unsigned int currentTournament = 0;
	unsigned int currentRound = 0;
	std::vector<Boop*> deadBoops;
	std::vector<std::vector<Boop*>> tournament;    // An arraylist for all the creatures
	std::vector<Food*> foods;
	b2World *physWorld;

	// Constructor
	World(b2World *physWorld, bool persist);

	void newFood();
	void resetFood();

	// Run the world
	void run();
	void render();
};