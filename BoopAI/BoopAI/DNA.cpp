#include "DNA.h"

DNA::DNA() {
	// DNA is random floating point values between 0 and 1 (!!)
	genes.resize(1);
	for (auto i = genes.begin(); i!=genes.end(); i++) {
		(*i) = (rand() / (double) (RAND_MAX + 1));
	}
}

DNA::DNA(std::vector<float> newgenes) {
	genes = newgenes;
}

// Based on a mutation probability, picks a new random character in array spots
void DNA::mutate(float m) {
	for (int i = 0; i < genes.size(); i++) {
		if ((rand() / (double) (RAND_MAX + 1)) < m) {
			genes[i] = (rand() / (double) (RAND_MAX + 1));
		}
	}
}

DNA *DNA::copy() {
	std::vector<float> newgenes(genes.size());
	for (int i = 0; i < newgenes.size(); i++) {
		newgenes[i] = genes[i];
	}

	return new DNA(newgenes);
}