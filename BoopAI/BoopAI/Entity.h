#pragma once

#define ET_BOOP 1
#define ET_FOOD 2

class Entity
{
public:
	virtual int getEntityType() = 0;
};

