#include "Boop.h"
#include <vector>
#include <iostream>
#include <GL\freeglut.h>
#include "Food.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	float answer = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return answer;
}

// Create a "boop" creature
Boop::Boop(Point *l, DNA *dna_) {
	location = l;
	health = 200;
	spawned = std::clock();
	foodEaten = 0;
	dna = dna_;
	// Gene 0 determines maxspeed and r
	// The bigger the boop, the slower it is
	r = 5;
	maxspeed = 7;
}

void Boop::run(Food *f) {
	update(f);
	borders();
	display();
}

// A boop can find food and eat it
void Boop::eat(Food *f) {
	// Are we touching any food objects?
	for (auto i = f->food.begin(); i != f->food.end();) {
		// If we are, juice up our strength!
		if (pow(((*i)->x - location->x), 2) + pow(((*i)->y - location->y), 2) < pow(r, 2)) {
			health += 200;
			foodEaten++;
			if (health > 1000)
				health = 1000;
			i = f->food.erase(i);
		}
		else {
			i++;
		}
	}
}

// At any moment there is a teeny, tiny chance a boop will reproduce
Boop *Boop::reproduce(Boop *parent) {
	// Child is exact copy of single parent
	DNA *childDNA = dna->copy();
	Point *location = new Point(rand() % WIDTH, rand() % HEIGHT);
	Boop *newBoop = new Boop(location, childDNA);
	std::vector<double> mother = nn.GetWeights();
	std::vector<double> father = parent->nn.GetWeights();
	std::vector<double> newweights;
	for (int i = 0; i != mother.size(); i++)
	{
		if (rand() % 1000 < 500)
		{
			newweights.push_back(mother.at(i));
		}
		else {
			newweights.push_back(father.at(i));
		}
	}
	newBoop->nn.PutWeights(newweights);
	newBoop->nn.mutateWeights();
	return newBoop;
}

// Method to update location
void Boop::update(Food *f) {

	//this will store all the inputs for the NN
	std::vector<double> inputs;

	//add in vector to closest food
	target = f->getClosest(location);
	if (target == NULL)
	{
		target = new Point(location->x, location->y);
	}
	inputs.push_back(target->x - location->x);
	inputs.push_back(target->y - location->y);

	//update the brain and get feedback
	std::vector<double> output = nn.update(inputs);
	if (output.size() < 2)
		return;
	float vx = map(output[0] - output[1], -1, 1, -maxspeed, maxspeed);
	float vy = map(output[2] - output[3], -1, 1, -maxspeed, maxspeed);
	*location += Point(vx, vy);
	// Death always looming
	health -= 0.8;
}

// Wraparound
void Boop::borders() {
	if (location->x < r)
	{
		location->x = r;
		health -= 100;
	}
	if (location->y < r)
	{
		location->y = r;
		health -= 100;
	}
	if (location->x > WIDTH - r)
	{
		location->x = WIDTH - r;
		health -= 100;
	}
	if (location->y > HEIGHT - r)
	{
		location->y = HEIGHT - r;
		health -= 100;
	}
}

// Method to display
void Boop::display() {
	//std::cout << "Drawing a Boop at " << location->x << " " << location->y << std::endl;
	glColor3f(1.f, map(health, 0, 200, 0, 1), map(health, 0, 200, 0, 1));
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14159265;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(location->x, location->y); // center of circle
	for (i = 0; i <= triangleAmount;i++) {
		glVertex2f(
			location->x + (r * cos(i *  twicePi / triangleAmount)),
			location->y + (r * sin(i * twicePi / triangleAmount))
			);
	}
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(location->x, location->y);
	glVertex2f(target->x, target->y);
	glEnd();
}

// Death
bool Boop::dead() {
	if (health < 0.0) {
		return true;
	}
	else {
		return false;
	}
}
