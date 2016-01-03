#pragma once
#include <vector>
#include "Boop.h"
#include "Food.h"
#include "ContactListener.h"
#include <chrono>

class Tournament
{
private:
	ContactListener *contactListener;
	std::chrono::milliseconds deltaTime;
	std::chrono::high_resolution_clock::time_point lastRun = std::chrono::high_resolution_clock::now();

public:
	vector<Boop*> deadBoops;
	Tournament();
	void setBoops(std::vector<Boop*> newBoops);
	void manageFood();
	std::vector<Food*> foods;
	std::vector<Boop*> boops;
	b2Body *groundBody;
	b2World *physWorld;
	void run();
	void reset();
};