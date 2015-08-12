#include "Food.h"

Food::Food(int num) {
	// Start with some food
	for (int i = 0; i < num; i++) {
		food.push_back(new Point(rand() % WIDTH, rand() % HEIGHT));
	}
}

// Add some food at a location
void Food::add(Point *l) {
	food.push_back(l);
}

// Display the food
void Food::run() {
	for (auto i = food.begin(); i != food.end(); i++) {

	}

	// There's a small chance food will appear randomly
	if (rand() < 0.001) {
		food.push_back(new Point(rand() % WIDTH, rand() % HEIGHT));
	}
}
