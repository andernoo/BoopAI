#pragma once
#include "Boop.h"
#include "Food.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <ctime>
#include <string>
#include <iomanip>
#include <future>
#include "Tournament.h"
#include <GL\glew.h>
#include <Box2D\Box2D.h>

#define NUM_PER_TOURNAMENT 80
#define NUM_TOURNAMENTS 2

class World
{
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