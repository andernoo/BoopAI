#include "Boop.h"
#include "MathUtilities.h"
#include <Box2D/Box2D.h>

Boop::Boop(b2World* world, int id) :
	id(id)
{
	spawned = std::clock();
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(mathRandom(30, WIDTH-30), mathRandom(30, HEIGHT-30));
	myBodyDef.angle = mathRandom(0, 359);
	body = world->CreateBody(&myBodyDef);
	body->SetUserData(this);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(20, 20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	body->CreateFixture(&fixtureDef);

	b2PolygonShape polyShape;
	fixtureDef.isSensor = true;
	fixtureDef.density = 0;
	fixtureDef.shape = &polyShape;

	b2Vec2 vertex[3] = {
		b2Vec2(10, 5),
		b2Vec2(50, 40),
		b2Vec2(50, 0),
	};
	polyShape.Set(vertex, 3);
	body->CreateFixture(&fixtureDef);

	vertex[0] = b2Vec2(10, -5);
	vertex[1] = b2Vec2(50, -40);
	vertex[2] = b2Vec2(50, 0);
	polyShape.Set(vertex, 3);
	body->CreateFixture(&fixtureDef);

	vertex[0] = b2Vec2(0, 0);
	vertex[1] = b2Vec2(70, 20);
	vertex[2] = b2Vec2(70, -20);
	polyShape.Set(vertex, 3);
	body->CreateFixture(&fixtureDef);
}


Boop::~Boop()
{
	body->GetWorld()->DestroyBody(body);
}

void Boop::step()
{
	inputs.clear();
	inputs.push_back(0);
	inputs.push_back(1);
	inputs.push_back(0);
	inputs.push_back(1);

	outputs = nn->update(inputs);

	b2Vec2 force((outputs[0]>outputs[1]?1:-1) * cos(body->GetAngle()), (outputs[0]>outputs[1] ? 1 : -1) * sin(body->GetAngle()));
	body->ApplyForce(force, body->GetPosition(), true);

	body->ApplyTorque((outputs[2]>outputs[3] ? 100 : -100), true);

	colour.x = (float)outputs[4] + 0.1f;
	colour.y = (float)outputs[5] + 0.1f;
	colour.z = (float)outputs[6] + 0.1f;
}
