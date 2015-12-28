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
		if (A && B)
		{
			if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
			{
				if (static_cast<Entity*>(B)->getEntityType() == ET_FOOD)
				{
					if (contact->GetFixtureA()->IsSensor())
					{
						contact->GetFixtureA()->SetUserData((void*) 10);
					}
				}
				if (static_cast<Entity*>(A)->getEntityType() == ET_FOOD)
				{
					if (contact->GetFixtureB()->IsSensor())
					{
						contact->GetFixtureB()->SetUserData((void*) 10);
					}
				}
				return;
			}
			if (static_cast<Entity*>(A)->getEntityType() == ET_FOOD && static_cast<Entity*>(B)->getEntityType() == ET_BOOP)
			{
					Boop *boop = static_cast<Boop*>(B);
					boop->eat(static_cast<Food*>(A));
			}
			else if (static_cast<Entity*>(B)->getEntityType() == ET_FOOD && static_cast<Entity*>(A)->getEntityType() == ET_BOOP)
			{
					Boop *boop = static_cast<Boop*>(A);
					boop->eat(static_cast<Food*>(B));
			}
		}
	}

	void EndContact(b2Contact* contact) 
	{
		if (contact->GetFixtureA()->IsSensor())
			contact->GetFixtureA()->SetUserData((void*) -10);
		if (contact->GetFixtureB()->IsSensor())
			contact->GetFixtureB()->SetUserData((void*) -10);
	}
};