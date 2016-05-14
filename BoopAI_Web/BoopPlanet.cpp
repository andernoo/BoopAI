#include "BoopPlanet.h"
#include "MathUtilities.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;

BoopPlanet::BoopPlanet(int numBoops, SimpleWeb::SocketServer<SimpleWeb::WS>* server) :
	server(server)
{
	world = new b2World(b2Vec2(0, 0));
	for(int i = 0; i < numBoops; i++) {
		boops.push_back(new Boop(world, i));
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.type = b2_staticBody;
	groundBody = world->CreateBody(&groundBodyDef);

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


BoopPlanet::~BoopPlanet()
{
}

void BoopPlanet::step()
{
	updateServer(boops, server);
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock().now() - lastRun);
	accumulator += deltaTime.count() / 100;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float step = 1.0f / 60.0f;
	while(accumulator >= step) {
		world->Step(step, velocityIterations, positionIterations);
		accumulator -= step;
		lastRun = std::chrono::high_resolution_clock().now();
	}
} 

void BoopPlanet::updateServer(std::vector<Boop*> boops, SimpleWeb::SocketServer<SimpleWeb::WS>* server)
{
	json j;
	for(auto i = boops.begin(); i != boops.end(); i++) {
		(*i)->step();
		Boop* boop = (*i);
		j["boops"][boop->id]["id"] = boop->id;
		j["boops"][boop->id]["x"] = boop->body->GetPosition().x;
		j["boops"][boop->id]["y"] = boop->body->GetPosition().y;
		j["boops"][boop->id]["vx"] = boop->body->GetLinearVelocity().x;
		j["boops"][boop->id]["vy"] = boop->body->GetLinearVelocity().y;
		j["boops"][boop->id]["angle"] = boop->body->GetAngle();
		j["boops"][boop->id]["r"] = boop->colour.x;
		j["boops"][boop->id]["g"] = boop->colour.y;
		j["boops"][boop->id]["b"] = boop->colour.z;
	}

	for(auto a_connection : server->get_connections()) {
		auto send_stream = std::make_shared<SimpleWeb::SocketServer<SimpleWeb::WS>::SendStream>();
		*send_stream << j.dump();
		server->send(a_connection, send_stream);
	}
}

Boop* BoopPlanet::getBoop(int boopId)
{
	return boops.at(boopId);
}

std::vector<Boop*> BoopPlanet::getBoops()
{
	return boops;
}