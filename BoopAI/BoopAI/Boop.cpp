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
	angle = 0;
	dna = dna_;
	// Gene 0 determines maxspeed and r
	// The bigger the boop, the slower it is
	r = map(dna->genes[0], 0, 1, 1, 30);
	maxspeed = map(r, 1, 50, 15, 1);
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
			health += 100;
			i = f->food.erase(i);
		}
		else {
			i++;
		}
	}
}

// At any moment there is a teeny, tiny chance a boop will reproduce
Boop *Boop::reproduce() {
	// Child is exact copy of single parent
	DNA *childDNA = dna->copy();
	// Child DNA can mutate
	childDNA->mutate(0.01);
	Point *location = new Point(rand() % WIDTH, rand() % HEIGHT);
	Boop *newBoop = new Boop(location, childDNA);
	newBoop->nn.PutWeights(nn.GetWeights());
	newBoop->nn.mutateWeights();
	return newBoop;
}

// Method to update location
void Boop::update(Food *f) {

	//this will store all the inputs for the NN
	std::vector<double> inputs;

	//add in vector to closest food
	target = f->getClosest(location);
	//target->normalise();
	inputs.push_back(target->x);
	inputs.push_back(target->y);

	//update the brain and get feedback
	std::vector<double> output = nn.update(inputs);
	if (output.size() < 2)
		return;
	float vx = map(output[0], 0, 1, -maxspeed, maxspeed);
	float vy = map(output[1], 0, 1, -maxspeed, maxspeed);
	*location += Point(vx, vy);
	// Death always looming
	health -= .4;
}

// Wraparound
void Boop::borders() {
	if (location->x < r)
	{
		location->x = r;
		health -= 10;
	}
	if (location->y < r) 
	{
		location->y = r; 
		health -= 10;
	}
	if (location->x > WIDTH - r) 
	{ 
		location->x = WIDTH - r; 
		health -= 10; 
	}
	if (location->y > HEIGHT - r) 
	{ 
		location->y = HEIGHT - r; 
		health -= 10;
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
