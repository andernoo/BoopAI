#include "DNA.h"

DNA::DNA() {
		// DNA is random floating point values between 0 and 1 (!!)
	genes.resize(1);
		for (int i = 0; i < genes.size(); i++) {
			genes[i] = rand();
		}
	}

DNA::DNA(std::vector<float> newgenes) {
		genes = newgenes;
	}

	// Based on a mutation probability, picks a new random character in array spots
void DNA::mutate(float m) {
		for (int i = 0; i < genes.size(); i++) {
			if (rand()%1 < m) {
				genes[i] = rand();
			}
		}
	}

DNA *DNA::copy() {
	std::vector<float> newgenes(genes.size(),1);
	for (int i = 0; i < newgenes.size(); i++) {
		newgenes[i] = genes[i];
	}

	return new DNA(newgenes);
}