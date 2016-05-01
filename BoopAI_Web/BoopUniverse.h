#pragma once
#include <vector>
#include "BoopPlanet.h"
class BoopUniverse
{
	std::vector<BoopPlanet*> planets;
public:
	BoopUniverse();
	~BoopUniverse();
	void step();
	BoopPlanet * getPlanet(int planetId);
	void addPlanet(int numBoops);
};

