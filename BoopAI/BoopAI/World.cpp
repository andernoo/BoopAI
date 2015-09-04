#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>

std::clock_t start;
double duration;

World::World(b2World *physWorld) :
physWorld(physWorld)
{
	int num = 20;
	// Start with initial food and creatures
	food = new Food(num);
	for (int i = 0; i < num; i++) {
		newBoop();
	}
	start = std::clock();
	glGenBuffers(1,&boopBuffer);
}

// Make a new creature
void World::newBoop(float x, float y) {
	Point *l = new Point(x, y);
	DNA *dna = new DNA();
	boops.push_back(new Boop(physWorld, l, dna));
}

bool sortBoops(Boop *lhs, Boop *rhs)
{
	return lhs->foodEaten > rhs->foodEaten;
}

// Run the world
void World::run() {
	// Deal with food
	food->run();

	// Cycle through the ArrayList backwards b/c we are deleting
	for (auto i = boops.begin(); i != boops.end();) {
		// All boops run and eat
		Boop *b = *i;
		b->run(food, boopBuffer);
		b->eat(food);

		// If it's dead, kill it and make food
		if (b->dead()) {
			static double winning = 0;
			static int foods = 0;
			b->survived = (std::clock() - b->spawned) / (float) CLOCKS_PER_SEC;

			static std::ofstream myfile;
			if (!myfile.is_open())
			{
				time_t t = time(0);   // get time now
				struct tm now;
				localtime_s(&now, &t);
				char buffer[80];
				strftime(buffer, 80, "%m-%d %I.%M.csv", &now);
				myfile.open(buffer, std::fstream::app);
				myfile << "Boop Life" << "," << "Boop Food" << "," << "Life Record" << "," << "Food Record" << "\n";
			} else {
				myfile << b->survived << "," << b->foodEaten << "," << winning << "," << foods << "\n";
			}

			if (b->survived > winning)
			{
				winning = b->survived;
				cout << "Life record!: " << b->survived;
			}
			if (b->foodEaten > foods)
			{
				foods = b->foodEaten;
				cout << " Food record!: " << b->foodEaten;
			}
			cout << endl;
			i = boops.erase(i);
			//food->add(b->body->GetPosition());
			physWorld->DestroyBody(b->body);
			delete b;
		}
		else {
			i++;
		}
	}
	if (boops.size() < 20)
	{
		if (boops.size() > 3)
		{
			std::sort(boops.begin(), boops.end(), sortBoops);
			boops.push_back(boops.at(0)->reproduce(boops.at(1)));
			boops.push_back(boops.at(1)->reproduce(boops.at(2)));
		}
		else {
			newBoop();
		}
	}
}