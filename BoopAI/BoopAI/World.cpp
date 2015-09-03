#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>

std::clock_t start;
double duration;

World::World(int num) :
	m_sizeOfGen(num) {
	// Start with initial food and creatures
	food = new Food(num);
	for (int i = 0; i < num; i++) {
		Point *l = new Point(rand() % WIDTH, rand() % HEIGHT);
		//std::cout << "New Boop at: " << l->x << " " << l->y << std::endl;
		DNA *dna = new DNA();
		boops.push_back(new Boop(l, dna));
	}
	start = std::clock();
}

// Make a new creature
void World::born(float x = rand() % WIDTH, float y = rand() % HEIGHT) {
	Point *l = new Point(x, y);
	DNA *dna = new DNA();
	boops.push_back(new Boop(l, dna));
}

bool sortBoops(Boop *lhs, Boop *rhs)
{
	//return (lhs->survived + 5 * lhs->foodEaten) > (rhs->survived + 5 * rhs->foodEaten);
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
		b->run(food);
		b->eat(food);

		// If it's dead, kill it and make food
		if (b->dead()) {
			static double winning = 0;
			static int foods = 0;
			b->survived = (std::clock() - b->spawned) / (double) CLOCKS_PER_SEC;

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
			food->add(b->location);
			delete b;
		}
		else {
			i++;
		}
	}
	if (boops.size() < 20)
	{
		std::sort(boops.begin(), boops.end(), sortBoops);
		Boop *newBoop = boops.at(0)->reproduce(boops.at(1));
		newBoop->r++;
		boops.push_back(newBoop);
	}
}