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
			std::cout << "A && B is true " << contact->GetFixtureA()->GetBody()->GetUserData() << ", " << contact->GetFixtureB()->GetBody()->GetUserData() << std::endl;
			Entity *eA = static_cast<Entity*>(A);
			Entity *eB = static_cast<Entity*>(B);
			//std::cout << eA->getEntityType() << std::endl;
			//std::cout << eB->getEntityType() << std::endl;

			/*if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
			{
				if(eB->getEntityType() == ET_FOOD)
				{
					contact->GetFixtureA()->SetUserData((void*)1);
				}
				if(eA->getEntityType() == ET_FOOD)
				{
					contact->GetFixtureB()->SetUserData((void*)1);
				}
				return;
			}
			else if(eA->getEntityType() == ET_FOOD && eB->getEntityType() == ET_BOOP)
			{
				Boop *boop = static_cast<Boop*>(B);
				boop->eat(static_cast<Food*>(A));
			}
			else if(eB->getEntityType() == ET_FOOD && eA->getEntityType() == ET_BOOP)
			{
				Boop *boop = static_cast<Boop*>(A);
				boop->eat(static_cast<Food*>(B));
			}*/
		}
		else
		{
			//std::cout << "A && B is false " << A << " " << B << std::endl;
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