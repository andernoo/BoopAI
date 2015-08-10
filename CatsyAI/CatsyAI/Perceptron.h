#pragma once
#include <vector>
class Perceptron {
public:
	//The Perceptron stores its weights and learning constants.
	std::vector<float> weights;
	float c = 0.01;

	Perceptron(int n);

	//Return an output based on inputs.
	float feedforward(float *inputs);

	//Output is a + 1 or -1.
	float activate(float sum);

	//Train the network against known data.
	void train(float *inputs, int desired);
};