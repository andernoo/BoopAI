#include "Food.h"
#include <GL\freeglut.h>

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
		Point *location = (*i);
		glColor3f(0.831, 0.749, 0);
			glBegin(GL_QUADS);
			glVertex3f(location->x - 1, location->y - 1, 0.0);
			glVertex3f(location->x + 1, location->y - 1, 0.0);
			glVertex3f(location->x + 1, location->y + 1, 0.0);
			glVertex3f(location->x - 1, location->y + 1, 0.0);
		glEnd();
	}

	// There's a small chance food will appear randomly
	if ((rand() / (double) (RAND_MAX + 1)) < 0.05) {
		food.push_back(new Point(rand() % WIDTH, rand() % HEIGHT));
	}
}

Point *Food::getClosest(Point *l)
{
	double closest_so_far = 99999;

	Point *vClosestObject = NULL;

	//cycle through mines to find closest
	for (int i = 0; i<food.size(); i++)
	{
		double distance = pow(food.at(i)->x - l->x, 2) + pow(food.at(i)->y - l->y, 2);
		if (distance < closest_so_far)
		{
			closest_so_far = distance;
			vClosestObject = food.at(i);
		}
	}
	return vClosestObject;
}
