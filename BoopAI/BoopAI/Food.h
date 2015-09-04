#pragma once
#include "Point.h"
#include <vector>
#include <Box2D\Box2D.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// Evolution EcoSystem

// A collection of food in the world

class Food {
	GLuint foodBuffer;
public:
	std::vector<b2Vec2> food;

	Food(int num);

	// Add some food at a location
	void add(b2Vec2 l);

	// Display the food
	void run();

	b2Vec2 getClosest(b2Vec2 l);
};