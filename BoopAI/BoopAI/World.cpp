#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>
#include <string>

World::World(b2World *physWorld, bool persist = false) :
	physWorld(physWorld)
{
	physWorld->SetContactListener(&contactListener);
	//if (persist)
	//{
	//	cout << "Using weights from persist.csv" << endl;
	//	std::vector<double> weights;
	//	ifstream file("persist.csv");
	//	string value;
	//	while (file.good())
	//	{
	//		getline(file, value, ',');
	//		weights.push_back(stod(value));
	//		cout << value;
	//	}
	//	cout << endl;
	//	for (int i = 0; i < NUM_PER_TOURNAMENT; i++) {
	//		newBoop(i, weights);
	//	}
	//}
	//else {

	for (int t = 0; t < NUM_TOURNAMENTS; t++)
	{
		std::vector<Boop*> boops;
		for (int i = 0; i < NUM_PER_TOURNAMENT; i++) {
			boops.push_back(new Boop(physWorld));
		}
		tournament.push_back(boops);
	}

	for (int i = 0; i < 30; i++) {
		newFood();
	}

	glGenBuffers(1, &foodBuffer);

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

bool sortBoops(Boop *lhs, Boop *rhs)
{
	return lhs->foodEaten > rhs->foodEaten;
}

void World::newFood() {
	foods.push_back(new Food(physWorld, &foods));
}

void World::render()
{
	for (auto i = foods.begin(); i != foods.end(); i++)
	{
		(*i)->render(foodBuffer);
	}

	vector<Boop*> boops = tournament.at(currentTournament);
	for (auto i = boops.begin(); i != boops.end(); i++)
	{
		(*i)->render();
	}

	glColor3f(0.4f, 0.4f, 0.4f);

	for (b2Fixture* fixture = groundBody->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		glBegin(GL_QUADS);
		b2PolygonShape *shape = (b2PolygonShape*) fixture->GetShape();
		for (int i = 0; i < shape->m_count; i++)
		{
			glVertex2f(shape->m_vertices[i].x, shape->m_vertices[i].y);
		}
		glEnd();
	}

	glColor3f(1.f, 1.f, 1.f);
	glPointSize(2);

	glBegin(GL_POINTS);
	for (b2Body *body = physWorld->GetBodyList(); body; body = body->GetNext())
	{
		glVertex2f(body->GetPosition().x, body->GetPosition().y);
	}
	glEnd();

	if(tournament.at(currentTournament).size()>0)
	{
		Boop *boop = tournament.at(currentTournament).at(0);
		std::vector<double> weights = boop->nn.GetWeights();
		int numWeights = boop->nn.GetNumberOfWeights();
		glColor4f(1, 1, 1, 0.4);
		glBegin(GL_POINTS);
		glPointSize(10);
		for (int i = 0; i < numWeights; i++)
		{
			//cout << weights.at(i) << ", ";
			glVertex2f(10, i);
		}
		glEnd();
	}
}

void World::resetFood()
{
	for (auto i = foods.begin(); i != foods.end();) {
		Food *food = (*i);
		delete food;
		i = foods.erase(i);
	}
	for (int i = 0; i < 30; i++) {
		newFood();
	}
}

void World::resetTournaments()
{
	currentTournament = 0;
	tournament.clear();
	std::sort(deadBoops.begin(), deadBoops.end(), sortBoops);
	cout << "GENERATION END " << endl;
	cout << "Winner ate: " << deadBoops.at(0)->foodEaten << endl;
	cout << "Winner survived: " << deadBoops.at(0)->survived << endl;
	for (int t = 0; t < NUM_TOURNAMENTS; t++)
	{
		std::vector<Boop*> boops;
		for (int i = 0; boops.size() < NUM_PER_TOURNAMENT-2; i++) 
		{
			boops.push_back(deadBoops.at(i)->reproduce(deadBoops.at(i + 1)));
			boops.push_back(deadBoops.at(i)->reproduce(deadBoops.at(i + 1)));
		}
		boops.push_back(deadBoops.at(0));
		boops.push_back(new Boop(physWorld));
		boops.push_back(new Boop(physWorld));
		tournament.push_back(boops);
	}
}

// Run the world
void World::run() {
	for (auto i = foods.begin(); i != foods.end();) {
		Food *food = (*i);
		if (food->eaten == true)
		{
			delete food;
			i = foods.erase(i);
		}
		else {
			i++;
		}
	}
	if (mathRandom(0, 1) < 0.01)
		newFood();

	if (tournament[currentTournament].size() == 0)
	{
		currentTournament++;
		resetFood();
		if (currentTournament >= NUM_TOURNAMENTS)
		{
			currentRound++;
			resetFood();
			resetTournaments();
		}

	}

	for (auto i = tournament[currentTournament].begin(); i != tournament[currentTournament].end();)
	{
		// All boops run and eat
		Boop *b = *i;
		b->update();

		// If it's dead, kill it and make food
		if (b->dead()) {
			static double winning = 0;
			static unsigned int foods = 0;

			static std::ofstream myfile;
			if (!myfile.is_open())
			{
				time_t t = time(0);   // get time now
				struct tm now;
				localtime_s(&now, &t);
				char buffer[80];
				strftime(buffer, 80, "%m-%d %I.%M.csv", &now);
				myfile.open(buffer, std::fstream::app);
				myfile << "Boop Life" << "," << "Boop Food" << "," << "Life Record" << "," << "Food Record\n";
			}
			else {
				myfile << b->survived << "," << b->foodEaten << "," << winning << "," << foods;
				vector<double> weights = tournament[currentTournament].at(0)->nn.GetWeights();
				for (auto i = weights.begin(); i != weights.end(); i++)
				{
					myfile << ',' << (*i);
				}
				myfile << '\n';
			}

			if (b->survived > winning && b->survived >= 20)
			{
				winning = b->survived;
				cout << "Life record!: " << b->survived << endl;;
			}
			if (b->foodEaten > foods && b->foodEaten >= 5)
			{
				foods = b->foodEaten;
				cout << " Food record!: " << b->foodEaten << endl;;
			}
			b->destroyBody();
			deadBoops.push_back(b);
			i = tournament[currentTournament].erase(i);
		}
		else {
			i++;
		}
	}
}