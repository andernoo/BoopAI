#pragma once

#define WIDTH 640
#define HEIGHT 480

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
	void operator+=(const Point& a)
	{
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