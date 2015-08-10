#pragma once

struct Point
{
	float x, y;

	// default + parameterized constructor
	Point(float x = 0, float y = 0)
		: x(x), y(y)
	{
	}

	// assignment operator modifies object, therefore non-const
	Point& operator=(const Point& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	// plusequals
	Point operator+=(const Point& a)
	{
		x += a.x;
		y += a.y;
	}

	// addop. doesn't modify object. therefore const.
	Point operator+(const Point& a) const
	{
		return Point(a.x + x, a.y + y);
	}

	// equality comparison. doesn't modify object. therefore const.
	bool operator==(const Point& a) const
	{
		return (x == a.x && y == a.y);
	}
};

class Boop {
	Point location; // Location
	DNA dna;          // DNA
	float health;     // Life timer
	float xoff;       // For perlin noise
	float yoff;
	// DNA will determine size and maxspeed
	float r;
	float maxspeed;

	// Create a "boop" creature
	Boop(Point l, DNA dna_);

	void run();

	// A boop can find food and eat it
	void eat(Food f);

	// At any moment there is a teeny, tiny chance a boop will reproduce
	Boop *reproduce();

	// Method to update location
	void update();

	// Wraparound
	void borders();

	// Method to display
	void display();

	// Death
	bool dead();
};