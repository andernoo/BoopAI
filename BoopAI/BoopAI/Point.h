#pragma once
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

struct Point
{
	float x, y;

	// default + parameterized constructor
	Point(float x = 0, float y = 0)
		: x(x), y(y)
	{
	}

	void normalise()
	{
		x = (x - -WIDTH) * (1 - -1) / (WIDTH - -WIDTH) + -1;
		y = (y - -HEIGHT) * (1 - -1) / (HEIGHT - -HEIGHT) + -1;
	}

	// assignment operator modifies object, therefore non-const
	Point& operator=(const Point& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	// plusequals
	void operator+=(const Point& a)
	{
		//std::cout << "X: " << x << std::endl << "New X: " << a.x << std::endl;
		x += a.x;
		y += a.y;
	}

	// addop. doesn't modify object. therefore const.
	Point *operator+(const Point& a) const
	{
		return &Point(a.x + x, a.y + y);
	}

	// equality comparison. doesn't modify object. therefore const.
	bool operator==(const Point& a) const
	{
		return (x == a.x && y == a.y);
	}
};