#pragma once
#include <vector>
#include "Boop.h"
#include <Box2D/Box2D.h>
#include <chrono>

class BoopPlanet
{
	std::chrono::milliseconds deltaTime;
	std::chrono::high_resolution_clock::time_point lastRun = std::chrono::high_resolution_clock::now();
	double accumulator;
	b2World* world;
	std::vector<Boop*> boops;
	b2Body* groundBody;
public:
	BoopPlanet(int numBoops);
	~BoopPlanet();
	void step();
	void step(float dt);
	Boop * getBoop(int boopId);
	std::vector<Boop*> getBoops();
};
