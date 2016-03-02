#include "tournament.h"

Tournament::Tournament()
{
	physWorld = new b2World(b2Vec2(0, 0));
	contactListener = new ContactListener;
	physWorld->SetContactListener(contactListener);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.type = b2_staticBody;
	groundBody = physWorld->CreateBody(&groundBodyDef);

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

void Tournament::setBoops(std::vector<Boop*> newBoops)
{
	boops = newBoops;
	for(Boop *boop : boops)
	{
		boop->addBody(physWorld);
		boop->health = 200;
		boop->survived = 0;
	}
}

void Tournament::manageFood()
{
}

bool boopPredicate(Boop *b)
{
	return b->m_markedForDeath;
}

bool foodPredicate(Food *f)
{
	return f->eaten;
}

void Tournament::run()
{
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock().now() - lastRun);

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	physWorld->Step(deltaTime.count(), velocityIterations, positionIterations);
	lastRun = std::chrono::high_resolution_clock().now();

	for(auto f = foods.begin(); f != foods.end(); f++)
	{
		Food *food = (*f);
		if(food->eaten == true)
		{
			physWorld->DestroyBody(food->body);
		}
	}
	foods.erase(std::remove_if(foods.begin(), foods.end(), foodPredicate), foods.end());

	while(foods.size() < 60)
	{
		foods.push_back(new Food(physWorld));
	}

	for(auto i = boops.begin(); i != boops.end(); i++)
	{
		Boop *b = (*i);
		b->update();

		if(b->dead())
		{
			physWorld->DestroyBody(b->body);
			deadBoops.push_back(b);
			b->m_markedForDeath = true;
		}
	}
	boops.erase(std::remove_if(boops.begin(), boops.end(), boopPredicate), boops.end());
}

void Tournament::reset()
{
}