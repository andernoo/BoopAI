#pragma once
#include <vector>
#include "Boop.h"
#include "ContactListener.h"

class Tournament
{
private:
	std::vector<Food*> foods;
	b2World *physWorld;
	b2Body *groundBody;
	ContactListener contactListener;
	std::vector<Boop*> boops;

public:
	Tournament();
	void setBoops(std::vector<Boop*> newBoops);
	void manageFood();
	void run();
};