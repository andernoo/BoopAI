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
	for (Boop *boop : boops)
	{
		boop->addBody(physWorld);
	}
}

vector<Boop*> Tournament::run()
{
	float32 timeStep = 1.0f / 20.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	physWorld->Step(timeStep, velocityIterations, positionIterations);

	while (foods.size() < 30)
	{
		foods.push_back(new Food(physWorld));
	}
	for (auto f = foods.begin(); f != foods.end();) {
		Food *food = (*f);
		if (food->eaten == true)
		{
			delete food;
			f = foods.erase(f);
		}
		else {
			f++;
		}
	}

	vector<Boop*> deadBoops;
	for (auto i = boops.begin(); i != boops.end();)
	{
		Boop *b = (*i);
		b->update();

		if (b->dead()) 
		{
			deadBoops.push_back(b);
			b->destroyBody(physWorld);
			i = boops.erase(i);
		}
		else {
			i++;
		}
	}
	return deadBoops;
}

void Tournament::reset()
{

}