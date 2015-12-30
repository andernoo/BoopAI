#include "Boop.h"
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "math_3d.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	float answer = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return answer;
}

Boop::~Boop()
{
}

// Create a "boop" creature
Boop::Boop()
{
}

void Boop::destroyBody(b2World *physWorld)
{
	survived = (std::clock() - spawned) / (float)CLOCKS_PER_SEC;
	physWorld->DestroyBody(body);
	body = NULL;
}

void Boop::addBody(b2World *physWorld)
{
	spawned = std::clock();
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set((float)(rand() % WIDTH), (float)(rand() % HEIGHT));
	myBodyDef.angle = ToRadian(mathRandom(0, 360));
	myBodyDef.linearDamping = 1;
	myBodyDef.angularDamping = 1;
	body = physWorld->CreateBody(&myBodyDef);
	body->SetUserData(this);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(10, 5);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.01f;
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
	//vertex[3] = b2Vec2(50, 5);
	polyShape.Set(vertex, 3);
	body->CreateFixture(&fixtureDef);
}

// A boop can find food and eat it
void Boop::eat(Food *food)
{
	health += 200;
	foodEaten++;
	if(health > 1000)
		health = 1000;
	//Don't delete food, add it to a remove list and process next. 
	//We're in the callback at this point
	food->eaten = true;
}

Boop *Boop::reproduce(Boop *parent)
{
	// Child is exact copy of single parent
	Boop *newBoop = new Boop();
	std::vector<double> mother = nn.GetWeights();
	std::vector<double> father = parent->nn.GetWeights();
	std::vector<double> newweights;
	for(int i = 0; i != mother.size(); i++)
	{
		if(rand() % 1000 < 500)
		{
			newweights.push_back(mother.at(i));
		}
		else
		{
			newweights.push_back(father.at(i));
		}
	}
	newBoop->nn.PutWeights(newweights);
	newBoop->nn.mutateWeights();
	return newBoop;
}

// Method to update location
void Boop::update()
{
	if(body == NULL)
		return;
	inputs.clear();

	for(b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if(fixture->IsSensor())
		{
			inputs.push_back(((int)fixture->GetUserData()) > 0 ? 10 : -10);
		}
	}

	//update the brain and get feedback
	std::vector<double> output = nn.update(inputs);

	if(output[0] > 0.65)
	{
		b2Vec2 force(1000 * output[0] * cos(body->GetAngle()), 1000 * output[0] * sin(body->GetAngle()));
		body->ApplyForce(force, body->GetPosition(), true);
	}
	else if(output[0] < 0.35)
	{
		b2Vec2 force(-1000 * output[0] * cos(body->GetAngle()), -1000 * output[0] * sin(body->GetAngle()));
		body->ApplyForce(force, body->GetPosition(), true);
	}

	body->ApplyTorque((output[1] - output[2]) * 200, true);


	colour.x = (float)output[3] + 0.1f;
	colour.y = (float)output[4] + 0.1f;
	colour.z = (float)output[5] + 0.1f;
	// Death always looming
	health -= 0.4f;
}

// Method to display
void Boop::render()
{
	if(body == NULL)
		return;
	float angle = body->GetAngle();
	b2Vec2 pos = body->GetPosition();

	glColor3f(colour.x, colour.y, colour.z);
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(ToDegree(angle), 0.0f, 0.0f, 1.0f);

	//Begin old graphics code
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-10, 5);
	glVertex2f(-10, -5);
	glVertex2f(0, 5);
	glVertex2f(0, -5);
	glColor3f(1, map(health, 0, 200, 0, 1), map(health, 0, 200, 0, 1));
	glVertex2f(10, 5);
	glVertex2f(10, -5);
	glEnd();
	glBegin(GL_TRIANGLES);
	for(b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if(fixture->IsSensor())
		{
			b2PolygonShape *shape = (b2PolygonShape*)fixture->GetShape();
			glColor4f(1, ((int)fixture->GetUserData()) > 0 ? 0 : 1.f, ((int)fixture->GetUserData()) > 0 ? 0 : 1.f, 0.15f);
			for(int i = 0; i < shape->m_count; i++)
			{
				glVertex2f(shape->m_vertices[i].x, shape->m_vertices[i].y);
			}
		}
	}
	glEnd();

	glPopMatrix();
}

// Death
bool Boop::dead()
{
	return health < 0.0;
}

int Boop::getEntityType()
{
	return ET_BOOP;
}