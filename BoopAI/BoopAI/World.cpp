#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>
#include <string>

World::World(b2World *physWorld, bool persist=false) :
physWorld(physWorld)
{
	// Start with initial food and creatures
	food = new Food(10);
	if (persist)
	{
		cout << "Using weights from persist.csv" << endl;
		std::vector<double> weights;
		ifstream file("persist.csv");
		string value;
		while (file.good())
		{
			getline(file, value, ',');
			weights.push_back(stod(value));
			cout << value;
		}
		cout << endl;
		for (int i = 0; i < 30; i++) {
			newBoop(weights);
		}
	}
	else {
		for (int i = 0; i < 30; i++) {
			newBoop();
		}
	}
	glGenBuffers(1,&boopBuffer);
}

bool sortBoops(Boop *lhs, Boop *rhs)
{
	return lhs->foodEaten > rhs->foodEaten;
}

// Make a new creature
void World::newBoop(std::vector<double> weights) {
	Point *l = new Point((float) (rand() % WIDTH), (float) (rand() % HEIGHT));
	DNA *dna = new DNA();
	Boop *boop = new Boop(physWorld, l, dna);
	boop->nn.PutWeights(weights);
	boops.push_back(boop);
}

void World::newBoop() {
	Point *l = new Point((float)(rand() % WIDTH), (float)(rand() % HEIGHT));
	DNA *dna = new DNA();
	boops.push_back(new Boop(physWorld, l, dna));
}

// Run the world
void World::run() {
	// Deal with food
	food->run();

	// Cycle through the ArrayList backwards b/c we are deleting
	for (auto i = boops.begin(); i != boops.end();) {
		// All boops run and eat
		Boop *b = *i;
		b->run(food, boopBuffer);
		b->eat(food);

		// If it's dead, kill it and make food
		if (b->dead()) {
			static double winning = 0;
			static int foods = 0;
			b->survived = (std::clock() - b->spawned) / (float) CLOCKS_PER_SEC;

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
			} else {
				myfile << b->survived << "," << b->foodEaten << "," << winning << "," << foods;
				vector<double> weights = boops.at(0)->nn.GetWeights();
				for (auto i = weights.begin(); i != weights.end(); i++)
				{
					myfile << ',' << (*i);
				}
				myfile << '\n';
			}

			if (b->survived > winning)
			{
				winning = b->survived;
				cout << "Life record!: " << b->survived << endl;;
			}
			if (b->foodEaten > foods)
			{
				foods = b->foodEaten;
				cout << " Food record!: " << b->foodEaten << endl;;
			}
			i = boops.erase(i);
			//food->add(b->body->GetPosition());
			physWorld->DestroyBody(b->body);
			delete b;
		}
		else {
			i++;
		}
	}

	if (boops.size() < 20)
	{
		int count=boops.size();
		if (count < 3) {
			newBoop();
		}
		else {
			std::sort(boops.begin(), boops.end(), sortBoops);
			for (int i = 1; i < count; i++)
			{
				boops.push_back(boops.at(i)->reproduce(boops.at(i - 1)));
			}
		}
	}
}