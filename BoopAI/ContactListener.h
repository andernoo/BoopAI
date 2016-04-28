#pragma once
#include <Box2D\Box2D.h>
#include <iostream>
#include "Entity.h"
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		if (contact->GetFixtureA()->IsSensor())
		{
			contact->GetFixtureA()->SetUserData((void*)((int)contact->GetFixtureA()->GetUserData()+1));
			return;
		}
		else if (contact->GetFixtureB()->IsSensor())
		{
			contact->GetFixtureB()->SetUserData((void*)((int)contact->GetFixtureB()->GetUserData() + 1));
			return;
		}

		void *A = contact->GetFixtureA()->GetBody()->GetUserData();
		void *B = contact->GetFixtureB()->GetBody()->GetUserData();
		if (A && B)
		{
			Entity *eA = static_cast<Entity*>(A);
			Entity *eB = static_cast<Entity*>(B);
			eA->contact(eB);
		}
	}

	void EndContact(b2Contact* contact)
	{
		if (contact->GetFixtureA()->IsSensor())
			contact->GetFixtureA()->SetUserData((void*)((int)contact->GetFixtureA()->GetUserData() - 1));
		if (contact->GetFixtureB()->IsSensor())
			contact->GetFixtureB()->SetUserData((void*)((int)contact->GetFixtureB()->GetUserData() - 1));
	}
};