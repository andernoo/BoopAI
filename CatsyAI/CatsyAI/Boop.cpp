#include "Boop.h"
#include <vector>

// Create a "boop" creature
Boop::Boop(Point l, DNA dna_) {
	location = l;
	health = 200;
	xoff = rand()%1000;
	yoff = rand()%1000;
	dna = dna_;
	// Gene 0 determines maxspeed and r
	// The bigger the boop, the slower it is
	maxspeed = map(dna.genes[0], 0, 1, 15, 0);
	r = map(dna.genes[0], 0, 1, 0, 50);
}

void Boop::run() {
	update();
	borders();
	display();
}

// A boop can find food and eat it
void Boop::eat(Food f) {
	std::vector<Point> food = f.getFood();
	// Are we touching any food objects?
	for (int i = food.size() - 1; i >= 0; i--) {
		Point foodLocation = food;
		float d = location-foodLocation;
		// If we are, juice up our strength!
		if (d < r / 2) {
			health += 100;
			food.remove(i);
		}
	}
}

// At any moment there is a teeny, tiny chance a boop will reproduce
Boop *Boop::reproduce() {
	// asexual reproduction
	if (rand() < 0.0005) {
		// Child is exact copy of single parent
		DNA childDNA = dna.copy();
		// Child DNA can mutate
		childDNA.mutate(0.01);
		return new Boop(location, childDNA);
	}
	else {
		return NULL;
	}
}

// Method to update location
void Boop::update() {
	// Simple movement based on perlin noise
	float vx = map(noise(xoff), 0, 1, -maxspeed, maxspeed);
	float vy = map(noise(yoff), 0, 1, -maxspeed, maxspeed);
	Point velocity = new Point(vx, vy);
	xoff += 0.01;
	yoff += 0.01;

	location+=velocity;
	// Death always looming
	health -= 0.2;
}

// Wraparound
void Boop::borders() {
	if (location.x < -r) location.x = width + r;
	if (location.y < -r) location.y = height + r;
	if (location.x > width + r) location.x = -r;
	if (location.y > height + r) location.y = -r;
}

// Method to display
void Boop::display() {
	ellipseMode(CENTER);
	stroke(0, health);
	fill(0, health);
	ellipse(location.x, location.y, r, r);
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
