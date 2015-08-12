#include "World.h"

World::World(int num) {
		// Start with initial food and creatures
		food = new Food(num);
		for (int i = 0; i < num; i++) {
			Point *l = new Point(rand()%WIDTH, rand()%HEIGHT);
			DNA *dna = new DNA();
			boops.push_back(new Boop(l, dna));
		}
	}

	// Make a new creature
	void World::born(float x, float y) {
		Point *l = new Point(x, y);
		DNA *dna = new DNA();
		boops.push_back(new Boop(l, dna));
	}

	// Run the world
	void World::run() {
		// Deal with food
		food->run();

		// Cycle through the ArrayList backwards b/c we are deleting
		for (auto i = boops.begin(); i != boops.end(); i++) {
			// All boops run and eat
			Boop *b = *i;
			b->run();
			b->eat(food);
			// If it's dead, kill it and make food
			if (b->dead()) {
				boops.erase(i);
				food->food.push_back(b->location);
			}
			// Perhaps this boop would like to make a baby?
			Boop *child = b->reproduce();
			if (child != NULL) boops.push_back(child);
		}
	}