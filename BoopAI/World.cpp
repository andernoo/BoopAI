#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>
#include <string>
#include <iomanip>

World::World(bool persist = false)
{
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
		tournaments.push_back(new Tournament());
		std::vector<Boop*> boops;
		for (int i = 0; i < NUM_PER_TOURNAMENT; i++) {
			boops.push_back(new Boop());
		}
		tournaments.at(t)->setBoops(boops);
	}
}

bool sortBoops(Boop *lhs, Boop *rhs)
{
	return lhs->foodEaten > rhs->foodEaten;
}

void World::render()
{
	/*for (auto i = foods.begin(); i != foods.end(); i++)
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
	glEnd();*/
}

void World::resetTournaments()
{
	std::sort(deadBoops.begin(), deadBoops.end(), sortBoops);
	cout << "----- GENERATION ENDS -----" << endl;
	cout << "Winner ate: " << deadBoops.at(0)->foodEaten << endl;
	cout << "Winner survived: " << deadBoops.at(0)->survived << endl << endl;
	cout << left << setw(27) << setfill('-') << "------ Top 5 Boops ------" << endl;
	cout << setfill(' ') << "    | Ate |   Survived" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << right << setw(3) << i + 1 << " |" << setw(4) << deadBoops.at(i)->foodEaten << " |" << setw(10) << deadBoops.at(i)->survived << "s" << endl;
	}
	cout << endl << endl;
	deadBoops.at(0)->foodEaten = 0;
	deadBoops.at(0)->survived = 0;
	for (int t = 0; t < NUM_TOURNAMENTS; t++)
	{
		tournaments.push_back(new Tournament());
		std::vector<Boop*> boops;
		for (int i = 0; boops.size() < NUM_PER_TOURNAMENT - 2; i++)
		{
			boops.push_back(deadBoops.at(i)->reproduce(deadBoops.at(i + 1)));
			boops.push_back(deadBoops.at(i)->reproduce(deadBoops.at(i + 1)));
		}
		boops.push_back(deadBoops.at(0));
		boops.push_back(new Boop());
		boops.push_back(new Boop());
		tournaments.at(t)->setBoops(boops);
	}
}

// Run the world
void World::run()
{
	for (auto i = tournaments.begin(); i != tournaments.end();)
	{

	}
}

void World::writeToFile(std::vector<Boop*> boops)
{
	for (auto i = boops.begin(); i != boops.end();)
	{
		static std::ofstream myfile;
		if (!myfile.is_open())
		{
			time_t t = time(0);   // get time now
			struct tm now;
			localtime_s(&now, &t);
			char buffer[80];
			strftime(buffer, 80, "%m-%d %I.%M.csv", &now);
			myfile.open(buffer, std::fstream::app);
			myfile << "Boop Life" << "," << "Boop Food\n";
		}
		else {
			myfile << (*i)->survived << "," << (*i)->foodEaten;
			vector<double> weights = (*i)->nn.GetWeights();
			for (auto i = weights.begin(); i != weights.end(); i++)
			{
				myfile << ',' << (*i);
			}
			myfile << '\n';
		}
	}
}