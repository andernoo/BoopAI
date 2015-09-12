#pragma once
#include "Box2D\Box2D.h"
#include <iostream>
#include "Entity.h"
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) 
	{
		Entity *A = (Entity *) contact->GetFixtureA()->GetBody()->GetUserData();
		Entity *B = (Entity *) contact->GetFixtureB()->GetBody()->GetUserData();
		std::cout << "CONTACT START " << A->getEntityType() << " " << B->getEntityType() << std::endl;
		if (A->getEntityType() == ET_FOOD)
		{
			if (B->getEntityType() == ET_BOOP)
			{
				Boop *boop = dynamic_cast<Boop*>(B);
				boop->eat(dynamic_cast<Food*>(A));
			}
		}
		else if (B->getEntityType() == ET_FOOD)
		{

		}
	}

	void EndContact(b2Contact* contact) 
	{
		std::cout << "CONTACT END" << std::endl;
	}
};