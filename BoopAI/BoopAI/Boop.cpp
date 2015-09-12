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
	physWorld->DestroyBody(body);
}

// Create a "boop" creature
Boop::Boop(b2World *physWorld, b2Vec2 l) :
	physWorld(physWorld)
{
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(l.x, l.y);
	myBodyDef.angle = ToRadian(mathRandom(0, 360));
	myBodyDef.linearDamping = 2;
	myBodyDef.angularDamping = 2;
	body = physWorld->CreateBody(&myBodyDef);
	body->SetUserData(this);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(10, 5);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 0.4f;
	body->CreateFixture(&boxFixtureDef);

	GLfloat points[] =
	{
		-10, -5,
		-10, 5,
		0, -5,
		0,5,
		10,-5,
		10,5,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//buffer is binded to context,set pipes:)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//glDeleteBuffers(1, &points_vbo);
}

// A boop can find food and eat it
void Boop::eat(Food *food) 
{
			health += 200;
			foodEaten++;
			if (health > 1000)
				health = 1000;
			delete food;
}

Boop *Boop::reproduce(Boop *parent) {
	// Child is exact copy of single parent
	Boop *newBoop = new Boop(physWorld, b2Vec2(mathRandom(0, WIDTH), mathRandom(0, HEIGHT)));
	std::vector<double> mother = nn.GetWeights();
	std::vector<double> father = parent->nn.GetWeights();
	std::vector<double> newweights;
	for (int i = 0; i != mother.size(); i++)
	{
		if (rand() % 1000 < 500)
		{
			newweights.push_back(mother.at(i));
		}
		else {
			newweights.push_back(father.at(i));
		}
	}
	newBoop->nn.PutWeights(newweights);
	newBoop->nn.mutateWeights();
	return newBoop;
}

// Method to update location
void Boop::update(vector<Food*> food) {

	//this will store all the inputs for the NN
	std::vector<double> inputs;

	b2Vec2 target(0, 0);

	inputs.push_back(map(target.x - body->GetPosition().x, -100, 100, -10, 10));
	inputs.push_back(map(target.y - body->GetPosition().y, -100, 100, -10, 10));
	//inputs.push_back(body->GetAngle());

	//update the brain and get feedback
	std::vector<double> output = nn.update(inputs);

	float magnitude = (float) (20000 * output[0]);
	b2Vec2 force = b2Vec2(cos(body->GetAngle()) * magnitude, sin(body->GetAngle()) * magnitude);

	body->ApplyForce(force, body->GetPosition(), true);

	body->ApplyTorque((float) (20000 * (output[1] - output[2])), true);

	colour.x = (float) output[3]+0.1f;
	colour.y = (float) output[4]+0.1f;
	colour.z = (float) output[5]+0.1f;
	// Death always looming
	health -= 0.4f;
}

// Method to display
void Boop::render(GLuint boopBuffer) {
	float angle = body->GetAngle();
	b2Vec2 pos = body->GetPosition();

	glColor3f(colour.x, colour.y, colour.z);
	glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		glRotatef(ToDegree(angle), 0.0f, 0.0f, 1.0f);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP,0,6);
		//glBegin(GL_LINES);
		//	glVertex2f(0,0);
		//	glVertex2f(100, 0);
		//glEnd();
	glPopMatrix();
}

// Death
bool Boop::dead() {
	return health < 0.0;
}

int Boop::getEntityType()
{
	return ET_BOOP;
}