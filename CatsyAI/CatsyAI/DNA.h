#pragma once
#include <stdlib.h>
#include <vector>
// Evolution EcoSystem
// Daniel Shiffman <http://www.shiffman.net>

// Class to describe DNA
// Has more features for two parent mating (not used in this example)

class DNA {
public:
	// The genetic sequence
	std::vector<float> genes;

	// Constructor (makes a random DNA)
	DNA();

	DNA(std::vector<float> newgenes);

	DNA operator=(const DNA& a) {
		genes = a.genes;
	}
	DNA *copy();

	// Based on a mutation probability, picks a new random character in array spots
	void mutate(float m);
};