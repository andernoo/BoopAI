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
			(*i)->survived = (std::clock() - start) / (double) CLOCKS_PER_SEC;
			deadBoops.push_back((*i));
			i = boops.erase(i);
			//food->add(b->location);
			//delete b;
		}
		else {
			i++;
		}
	}
	if (boops.size() == 0)
	{
		static int generation = 0;
		generation++;
		duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		static std::ofstream myfile;
		if (!myfile.is_open())
		{
			time_t t = time(0);   // get time now
			struct tm now;
			localtime_s(&now, &t);
			char buffer[80];
			strftime(buffer, 80, "%m-%d %I.%M.csv", &now);
			myfile.open(buffer, std::fstream::app);
		}
		myfile << generation << "," << duration << "\n";
		std::cout << "Epoch time: " << duration << '\n';

		vector<Boop*> newboops;
		std::sort(deadBoops.begin(), deadBoops.end(), sortBoops);
		cout << "Top Three Boops: " << endl;
		cout << "1) " << deadBoops.at(0)->survived + 5 * deadBoops.at(0)->foodEaten << endl;
		cout << "2) " << deadBoops.at(1)->survived + 5 * deadBoops.at(1)->foodEaten << endl;
		cout << "3) " << deadBoops.at(2)->survived + 5 * deadBoops.at(2)->foodEaten << endl;
		for (auto i = deadBoops.begin(); i != deadBoops.begin() + 10;) {
			Boop *a = *i;
			a->health = 200;
			a->foodEaten = 0;
			a->survived = 0;
			a->r += 2;
			a->location->x = rand() % WIDTH;
			a->location->y = rand() % HEIGHT;

			i = std::next(i);
			Boop *b = *i;
			b->health = 200;
			b->foodEaten = 0;
			b->survived = 0;
			b->r += 2;
			b->location->x = rand() % WIDTH;
			b->location->y = rand() % HEIGHT;

			newboops.push_back(a->reproduce(b));
			newboops.push_back(b->reproduce(a));
			i = std::next(i);
		}
		deadBoops.clear();
		boops.clear();
		boops = newboops;
		delete food;
		food = new Food(m_sizeOfGen);
		start = std::clock();
		duration = 0;
	}
}