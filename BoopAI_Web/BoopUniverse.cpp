#include "BoopUniverse.h"



BoopUniverse::BoopUniverse(SimpleWeb::SocketServer<SimpleWeb::WS> *server) :
	server(server)
{
}


BoopUniverse::~BoopUniverse()
{
}

void BoopUniverse::step()
{
	for(auto i = planets.begin(); i != planets.end(); i++)
	{
		(*i)->step();
	}
}

BoopPlanet* BoopUniverse::getPlanet(int planetId)
{
	return planets.at(planetId);
}

void BoopUniverse::addPlanet(int numBoops)
{
	planets.push_back(new BoopPlanet(numBoops, server));
}