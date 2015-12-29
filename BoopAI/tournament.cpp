#include "tournament.h"

Tournament::Tournament()
{
	physWorld = new b2World(b2Vec2(0, 0));
	physWorld->SetContactListener(&contactListener);
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
}

void Tournament::manageFood()
{
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
}

void Tournament::run()
{
	manageFood();

	for (auto i = boops.begin(); i != boops.end();)
	{
		Boop *b = (*i);
		b->update();

		if (b->dead()) {
			b->destroyBody();
			i = boops.erase(i);
		}
		else {
			i++;
		}
	}
}