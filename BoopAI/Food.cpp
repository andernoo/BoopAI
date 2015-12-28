#include "Food.h"
#include <Box2D\Box2D.h>
#include "math_3d.h"

Food::Food(b2World *physWorld, std::vector<Food*> *food) :
	physWorld(physWorld), foods(food)
{
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(mathRandom(0, WIDTH), mathRandom(0, HEIGHT));
	myBodyDef.bullet = true;
	body = physWorld->CreateBody(&myBodyDef);
	body->SetUserData(this);
	b2CircleShape circleShape;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 0;
	body->CreateFixture(&fixtureDef);
}

Food::~Food()
{
	physWorld->DestroyBody(body);
}

void Food::render(GLuint foodBuffer)
{
	glColor3f(0.831f, 0.749f, 0);
	Vector2f Vertices[1];
	Vertices[0] = Vector2f(body->GetPosition().x, body->GetPosition().y);
	glPointSize(4);
	glBindBuffer(GL_ARRAY_BUFFER, foodBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
}

int Food::getEntityType()
{
	return ET_FOOD;
}