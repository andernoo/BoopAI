#pragma once
#include "Point.h"
#include <vector>
// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// Evolution EcoSystem

// A collection of food in the world

class Food {
public:
	std::vector<Point*> food;

	Food(int num);

	// Add some food at a location
	void add(Point *l);

	// Display the food
	void run();
};