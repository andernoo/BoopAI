#include "BoopPlanet.h"
#include "MathUtilities.h"
#include <iostream>
#include <iomanip>

BoopPlanet::BoopPlanet(int numBoops)
{
	world = new b2World(b2Vec2(0, 0));
	for(int i = 0; i < numBoops; i++)
	{
		boops.push_back(new Boop(world, i));
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.type = b2_staticBody;
	groundBody = world->CreateBody(&groundBodyDef);

	b2FixtureDef fixtureDef;

	b2PolygonShape polyShape;
	fixtureDef.density = 0;
	fixtureDef.shape = &polyShape;

	b2Vec2 vertex[4] = {
		b2Vec2(0, 0),
		b2Vec2(0, HEIGHT),
		b2Vec2(10, HEIGHT),
		b2Vec2(10,0)
	};
	polyShape.Set(vertex, 4);
	groundBody->CreateFixture(&fixtureDef);

	vertex[0] = b2Vec2(0, 0);
	vertex[1] = b2Vec2(0, 10);
	vertex[2] = b2Vec2(WIDTH, 10);
	vertex[3] = b2Vec2(WIDTH, 0);
	polyShape.Set(vertex, 4);
	groundBody->CreateFixture(&fixtureDef);

	vertex[0] = b2Vec2(0, HEIGHT);
	vertex[1] = b2Vec2(0, HEIGHT - 10);
	vertex[2] = b2Vec2(WIDTH, HEIGHT - 10);
	vertex[3] = b2Vec2(WIDTH, HEIGHT);
	polyShape.Set(vertex, 4);
	groundBody->CreateFixture(&fixtureDef);

	vertex[0] = b2Vec2(WIDTH - 10, 0);
	vertex[1] = b2Vec2(WIDTH, 0);
	vertex[2] = b2Vec2(WIDTH, HEIGHT);
	vertex[3] = b2Vec2(WIDTH - 10, HEIGHT);
	polyShape.Set(vertex, 4);
	groundBody->CreateFixture(&fixtureDef);
}


BoopPlanet::~BoopPlanet()
{
}

void BoopPlanet::step()
{
	for(auto i = boops.begin(); i != boops.end(); i++)
	{
		(*i)->step();
	}

	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock().now() - lastRun);
	accumulator += deltaTime.count()/100;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float step = 1.0 / 60.0;
	while(accumulator >= step)
	{
		world->Step(step, velocityIterations, positionIterations);
		accumulator -= step;
		lastRun = std::chrono::high_resolution_clock().now();
	}
}

Boop* BoopPlanet::getBoop(int boopId)
{
	return boops.at(boopId);
}

std::vector<Boop*> BoopPlanet::getBoops()
{
	return boops;
}