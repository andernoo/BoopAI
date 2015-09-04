#include "Boop.h"
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Food.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	float answer = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return answer;
}

// Create a "boop" creature
Boop::Boop(b2World *physWorld, Point *l, DNA *dna_) :
physWorld(physWorld) 
{
	location = l;
	health = 200;
	spawned = std::clock();
	foodEaten = 0;
	dna = dna_;
	// Gene 0 determines maxspeed and r
	// The bigger the boop, the slower it is
	r = 5;
	maxspeed = 7;

	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(l->x, l->y);
	myBodyDef.linearDamping = 2;
	myBodyDef.angularDamping = 2;
	body = physWorld->CreateBody(&myBodyDef);

	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = r; //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;
	body->CreateFixture(&myFixtureDef);
	body->SetTransform(body->GetPosition(), rand() % 3);
}

void Boop::run(Food *f, GLuint boopBuffer) {
	update(f);
	display(boopBuffer);
}

// A boop can find food and eat it
void Boop::eat(Food *f) {
	// Are we touching any food objects?
	for (auto i = f->food.begin(); i != f->food.end();) {
		// If we are, juice up our strength!
		if (pow(((*i).x - body->GetPosition().x), 2) + pow(((*i).y - body->GetPosition().y), 2) < pow(r, 2)) {
			health += 200;
			foodEaten++;
			if (health > 1000)
				health = 1000;
			i = f->food.erase(i);
		}
		else {
			i++;
		}
	}
}

Boop *Boop::reproduce(Boop *parent) {
	// Child is exact copy of single parent
	DNA *childDNA = dna->copy();
	Point *location = new Point(rand() % WIDTH, rand() % HEIGHT);
	Boop *newBoop = new Boop(physWorld, location, childDNA);
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
void Boop::update(Food *f) {

	//this will store all the inputs for the NN
	std::vector<double> inputs;
	r = map(health, 0, 1000, 5, 15);

	//add in vector to closest food
	target = f->getClosest(body->GetPosition());
	if (!target.IsValid())
	{
		target = b2Vec2(body->GetPosition().x, body->GetPosition().y);
	}
	inputs.push_back(target.x - body->GetPosition().x);
	inputs.push_back(target.y - body->GetPosition().y);
	inputs.push_back(body->GetAngle());
	inputs.push_back(map(health,0,1000,-10,10));

	//update the brain and get feedback
	std::vector<double> output = nn.update(inputs);
	
	float magnitude = 20000*output[0];
	b2Vec2 force = b2Vec2(cos(body->GetAngle()) * magnitude, sin(body->GetAngle()) * magnitude);

	body->ApplyForce(force, body->GetPosition(),true);

	body->ApplyTorque(20000 * output[1], true);
	body->ApplyTorque(20000 * -output[2], true);

	// Death always looming
	health -= 0.8f;
}

// Method to display
void Boop::display(GLuint boopBuffer) {
	float angle = body->GetAngle();
	b2Vec2 pos = body->GetPosition();

	glColor3f(1.f, map(health, 0, 200, 0, 1), map(health, 0, 200, 0, 1));

	Vector3f Vertices[3];
	Vertices[0] = Vector3f(pos.x+r, pos.y, 0.0f);
	Vertices[1] = Vector3f(pos.x-r, pos.y-r, 0.0f);
	Vertices[2] = Vector3f(pos.x-r, pos.y+r, 0.0f);
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(ToDegree(angle), 0.0f, 0.0f, 1.0f);
	glTranslatef(-pos.x, -pos.y, 0);
	
	glPointSize(2*r);

	glBindBuffer(GL_ARRAY_BUFFER, boopBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, boopBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glPopMatrix();

	//int triangleAmount = 10; //# of triangles used to draw circle

	//GLfloat twicePi = 2.0f * 3.14159265;

	//glPushMatrix();
	//	glRotatef(angle * 3.141592653589793 / 180.0, 0, 0, 1);
	//	glBegin(GL_TRIANGLE_FAN);
	//	glVertex2f(pos.x, pos.y); // center of circle
	//	for (int i = 0; i <= triangleAmount;i++) {
	//		glVertex2f(
	//			pos.x + (r * cos(i *  twicePi / triangleAmount)),
	//			pos.y + (r * sin(i * twicePi / triangleAmount))
	//			);
	//	}
	//	glEnd();

	//	glBegin(GL_LINES);
	//		glVertex2f(pos.x, pos.y);
	//		glVertex2f(target.x, target.y);
	//	glEnd();

	//	glBegin(GL_LINES);
	//		glVertex2f(pos.x, pos.y);
	//		glVertex2f(pos.x + 20, pos.y);
	//	glEnd();
	//glPopMatrix();
}

// Death
bool Boop::dead() {
	if (health < 0.0) {
		return true;
	}
	else {
		return false;
	}
}
