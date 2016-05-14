#pragma once
#include <vector>
#include "Boop.h"
#include <Box2D/Box2D.h>
#include <chrono>
#include "server_ws.hpp"

class BoopPlanet
{
	unsigned char numIterations = 50;
	std::chrono::milliseconds deltaTime;
	std::chrono::high_resolution_clock::time_point lastRun = std::chrono::high_resolution_clock::now();
	double accumulator;
	b2World* world;
	std::vector<Boop*> boops;
	b2Body* groundBody;
	SimpleWeb::SocketServer<SimpleWeb::WS>* server;
public:
	BoopPlanet(int numBoops, SimpleWeb::SocketServer<SimpleWeb::WS>* server);
	~BoopPlanet();
	void step();
	static void updateServer(std::vector<Boop*> boops, SimpleWeb::SocketServer<SimpleWeb::WS>* server);
	void step(float dt);
	Boop * getBoop(int boopId);
	std::vector<Boop*> getBoops();
};
