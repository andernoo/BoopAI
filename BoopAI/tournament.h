#pragma once
#include <vector>
#include "Boop.h"
#include "Food.h"
#include "ContactListener.h"

class Tournament
{
private:
	ContactListener *contactListener;

public:
	Tournament();
	void setBoops(std::vector<Boop*> newBoops);
	void manageFood();
	std::vector<Food*> foods;
	std::vector<Boop*> boops;
	b2Body *groundBody;
	b2World *physWorld;
	vector<Boop*> run();
	void reset();
};