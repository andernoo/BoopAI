#pragma once
#include <vector>
#include "BoopPlanet.h"
#include "server_ws.hpp"

class BoopUniverse
{
	std::vector<BoopPlanet*> planets;
	SimpleWeb::SocketServer<SimpleWeb::WS>* server;
public:
	BoopUniverse(SimpleWeb::SocketServer<SimpleWeb::WS> *server);
	~BoopUniverse();
	void step();
	BoopPlanet * getPlanet(int planetId);
	void addPlanet(int numBoops);
};

