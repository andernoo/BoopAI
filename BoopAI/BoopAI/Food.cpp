#include "Food.h"
#include <Box2D\Box2D.h>
#include "math_3d.h"

Food::Food(int num) {
	// Start with some food
	for (int i = 0; i < num; i++) {
		food.push_back(b2Vec2(rand() % WIDTH, rand() % HEIGHT));
	}
	glGenBuffers(1, &foodBuffer);
}

// Add some food at a location
void Food::add(b2Vec2 l) {
	food.push_back(l);
}

// Display the food
void Food::run() {
	for (auto i = food.begin(); i != food.end(); i++) {
		b2Vec2 location = (*i);
		glColor3f(0.831, 0.749, 0);
		Vector3f Vertices[1];
		Vertices[0] = Vector3f(location.x, location.y, 0.0f);
		glPointSize(1);
		glBindBuffer(GL_ARRAY_BUFFER, foodBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, foodBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, 1);
		glDisableVertexAttribArray(0);
	}

	// There's a small chance food will appear randomly
	if ((rand() / (double) (RAND_MAX + 1)) < 0.05) {
		food.push_back(b2Vec2(rand() % WIDTH, rand() % HEIGHT));
	}
}

b2Vec2 Food::getClosest(b2Vec2 l)
{
	double closest_so_far = 99999;

	b2Vec2 vClosestObject;

	//cycle through mines to find closest
	for (int i = 0; i<food.size(); i++)
	{
		double distance = pow(food.at(i).x - l.x, 2) + pow(food.at(i).y - l.y, 2);
		if (distance < closest_so_far)
		{
			closest_so_far = distance;
			vClosestObject = food.at(i);
		}
	}
	return vClosestObject;
}
