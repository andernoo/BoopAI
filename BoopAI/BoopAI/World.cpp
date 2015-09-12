#include "World.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <ctime>
#include <string>

World::World(b2World *physWorld, bool persist=false) :
physWorld(physWorld)
{
	//in FooTest constructor
	physWorld->SetContactListener(&contactListener);
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
	for (int i = 0; i < 30; i++) {
		newFood();
	}
	glGenBuffers(1, &boopBuffer);
	glGenBuffers(1, &foodBuffer);
}

bool sortBoops(Boop *lhs, Boop *rhs)
{
	return lhs->foodEaten > rhs->foodEaten;
}

// Make a new creature
void World::newBoop(std::vector<double> weights) {
	Boop *boop = new Boop(physWorld, b2Vec2((float)(rand() % WIDTH), (float) (rand() % HEIGHT)));
	boop->nn.PutWeights(weights);
	boops.push_back(boop);
}

void World::newBoop() {
	boops.push_back(new Boop(physWorld, b2Vec2((float) (rand() % WIDTH), (float) (rand() % HEIGHT))));
}

void World::newFood() {
	foods.push_back(new Food(physWorld, &foods));
}

void World::render()
{
	for (auto i = foods.begin(); i != foods.end(); i++) {
		Food *f = *i;
		f->render(foodBuffer);
	}
	for (auto i = boops.begin(); i != boops.end(); i++) {
		Boop *b = *i;
		b->render(boopBuffer);
	}
}

// Run the world
void World::run() {
	//cout << "BODIES: " << physWorld->GetBodyCount() << " FOODS: " << foods.size() << " BOOPS: " << boops.size() << endl;
	// Cycle through the ArrayList backwards b/c we are deleting
	if (mathRandom(0, 1) < 0.01)
		newFood();
	for (auto i = boops.begin(); i != boops.end();) {
		// All boops run and eat
		Boop *b = *i;
		b->update(foods);

		// If it's dead, kill it and make food
		if (b->dead()) {
			static double winning = 0;
			static unsigned int foods = 0;
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
			i = boops.erase(i);
			delete b;
		}
		else {
			i++;
		}
	}

	if (boops.size() < 30)
	{
		int count = boops.size();
		std::sort(boops.begin(), boops.end(), sortBoops);
		if (boops.size() <	2) {
			newBoop();
		}
		else {
			for (int i = 1; i != count; i++)
			{
				Boop *mother = boops.at(i);
				Boop *father = boops.at(i-1);
				boops.push_back(mother->reproduce(father));
			}
		}
	}
}