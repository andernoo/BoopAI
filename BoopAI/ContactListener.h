#pragma once
#include <Box2D\Box2D.h>
#include <iostream>
#include "Entity.h"
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		void *A = contact->GetFixtureA()->GetBody()->GetUserData();
		void *B = contact->GetFixtureB()->GetBody()->GetUserData();
		if(A && B)
		{
			Entity *eA = static_cast<Entity*>(A);
			Entity *eB = static_cast<Entity*>(B);
			eA->contact(eB);
		}
	}

	void EndContact(b2Contact* contact)
	{
		if(contact->GetFixtureA()->IsSensor())
			contact->GetFixtureA()->SetUserData((void*)-1);
		if(contact->GetFixtureB()->IsSensor())
			contact->GetFixtureB()->SetUserData((void*)-1);
	}
};