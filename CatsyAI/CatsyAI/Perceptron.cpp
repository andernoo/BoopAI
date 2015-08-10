#include "Perceptron.h"
#include <stdlib.h>
#include <iostream>

Perceptron::Perceptron(int n) {
	weights.resize(n);
	//weights start off random.
	for(int i = 0; i < (int) weights.size(); i++) {
		weights[i] = rand()%1==0?-1:1;
	}
}

//Return an output based on inputs.
float Perceptron::feedforward(float *inputs) {
	float sum = 0;
	for (int i = 0; i < (int) weights.size(); i++) {
		sum += inputs[i] * weights[i];
	}
	return activate(sum);
}

float Perceptron::activate(float sum) {
	if(sum>0) return 0.02;
	else return -0.02;
}

//Train the network against known data.
void Perceptron::train(float *inputs, int desired) {
	int guess = feedforward(inputs);
	float error = desired - guess;
	for (int i = 0; i < (int)weights.size(); i++) {
		weights[i] += c * error * inputs[i];
	}
}