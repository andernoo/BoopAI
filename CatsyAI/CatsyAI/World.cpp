#include "World.h"
#include <iostream>
#include <ctime>

std::clock_t start;
double duration;

World::World(int num) :
	m_sizeOfGen(num) {
	// Start with initial food and creatures
	food = new Food(num);
	for (int i = 0; i < num; i++) {
		Point *l = new Point(rand() % WIDTH, rand() % HEIGHT);
		std::cout << "New Boop at: " << l->x << " " << l->y << std::endl;
		DNA *dna = new DNA();
		boops.push_back(new Boop(l, dna));
	}
	start = std::clock();
}

// Make a new creature
void World::born(float x= rand() % WIDTH, float y=rand() % HEIGHT) {
	Point *l = new Point(x, y);
	DNA *dna = new DNA();
	boops.push_back(new Boop(l, dna));
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

		// Perhaps this boop would like to make a baby?
		//Boop *child = b->reproduce();
		//if (child != NULL) {
		//	boops.push_back(child);
		//}

		// If it's dead, kill it and make food
		if (b->dead()) {
			i = boops.erase(i);
			food->add(b->location);
			delete b;
		}
		else {
			i++;
		}
	}
	if (boops.size() < 4)
	{
		static int generation = 0;
		generation++;
		duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		ofstream myfile;
		myfile.open("example.csv",std::fstream::app);
		myfile << generation <<","<< duration << "\n";
		myfile.close();
		std::cout << "Epoch time: " << duration << '\n';
		vector<Boop*> newboops;
		for (auto i = boops.begin(); i != boops.end(); i++) {
			Boop *b = *i;
			Boop *child = b->reproduce();
			b->health = 200;
			b->location->x = rand() % WIDTH;
			b->location->y = rand() % HEIGHT;
			newboops.push_back(child);
			newboops.push_back(b);
		}
		boops = newboops;
		while (boops.size() < m_sizeOfGen)
		{
			born();
		}
		delete food;
		food = new Food(m_sizeOfGen*2);
		start = std::clock();
		duration = 0;
	}
}