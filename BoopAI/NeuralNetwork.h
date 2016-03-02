#pragma once
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

//-------------------------------------------------------------------
//	define neuron struct
//-------------------------------------------------------------------
struct Neuron
{
	//the number of inputs into the neuron
	int				      m_NumInputs;

	//the weights for each input
	vector<double>	m_vecWeight;


	//ctor
	Neuron(int NumInputs);
};


//---------------------------------------------------------------------
//	struct to hold a layer of neurons.
//---------------------------------------------------------------------

struct NeuronLayer
{
	//the number of neurons in this layer
	int					      m_NumNeurons;

	//the layer of neurons
	vector<Neuron>		m_vecNeurons;

	NeuronLayer(int NumNeurons,
		int NumInputsPerNeuron);
};


//----------------------------------------------------------------------
//	neural net class
//----------------------------------------------------------------------

class NeuralNetwork
{
private:
	int	m_NumInputs;
	int m_NumOutputs;
	int m_NumHiddenLayers;
	int m_NeuronsPerHiddenLayer;

	//storage for each layer of neurons including the output layer
	vector<NeuronLayer>	m_vecLayers;

public:
	NeuralNetwork(int numInputs, int numHidden, int numOutputs, int numPerHidden);
	void CreateNet();

	//gets the weights from the NN
	vector<double>	getWeights()const;

	//returns total number of weights in net
	int	GetNumberOfWeights()const;

	//replaces the weights with new ones
	void setWeights(vector<double> &weights);

	//calculates the outputs from a set of inputs
	vector<double> update(vector<double> &inputs);

	//sigmoid response curve
	inline double Sigmoid(double activation, double response);
	void mutateWeights();
};