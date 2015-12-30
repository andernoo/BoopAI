#include "Food.h"

Food::Food(b2World *physWorld)
{
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(mathRandom(0, WIDTH), mathRandom(0, HEIGHT));
	myBodyDef.bullet = true;
	body = physWorld->CreateBody(&myBodyDef);
	body->SetUserData((void*)"Test");
	b2CircleShape circleShape;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 0;
	body->CreateFixture(&fixtureDef);
}

Food::~Food()
{
}

int Food::getEntityType()
{
	return ET_FOOD;
}