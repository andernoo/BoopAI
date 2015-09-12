#pragma once

#include <stdio.h>
#define _USE_MATH_DEFINES 
#include <cmath>
#include "Box2D\Box2D.h"

float mathRandom(float min, float max);
double pointDistance(b2Vec2 one, b2Vec2 two);

#define WIDTH 1280
#define HEIGHT 720

#define ToRadian(x) (float)(((x) * 3.1415 / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415))

struct Vector2i
{
	int x;
	int y;
};

struct Vector2f
{
	float x;
	float y;

	Vector2f()
	{
	}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};


struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f()
	{
	}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(float f)
	{
		x = y = z = f;
	}

	Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const float*() const
	{
		return &(x);
	}

	Vector3f Cross(const Vector3f& v) const;

	Vector3f& Normalize();

	void Rotate(float Angle, const Vector3f& Axis);

	void Print() const
	{
		printf("(%.02f, %.02f, %.02f)", x, y, z);
	}
};


struct Vector4f
{
	float x;
	float y;
	float z;
	float w;

	Vector4f()
	{
	}

	Vector4f(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Print() const
	{
		printf("(%.02f, %.02f, %.02f, %.02f)", x, y, z, w);
	}
};

inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

struct PersProjInfo
{
	float FOV;
	float Width;
	float Height;
	float zNear;
	float zFar;
};

struct Quaternion
{
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w);

	void Normalize();

	Quaternion Conjugate();
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);