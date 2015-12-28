#pragma once

#define ET_BOOP 1
#define ET_FOOD 2
#define ET_WORLD 3

class Entity
{
public:
	virtual int getEntityType() = 0;
};

