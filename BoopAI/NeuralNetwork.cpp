#include "NeuralNetwork.h"
#include "math_3d.h"
#include <iostream>

Neuron::Neuron(int NumInputs) : m_NumInputs(NumInputs + 1)

{
	//we need an additional weight for the bias hence the +1
	for (int i = 0; i < NumInputs + 1; ++i)
	{
		//set up the weights with an initial random value
		m_vecWeight.push_back(-1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - -1))));
	}
}

NeuronLayer::NeuronLayer(int NumNeurons,
	int NumInputsPerNeuron) : m_NumNeurons(NumNeurons)
{
	for (int i = 0; i < NumNeurons; ++i)

		m_vecNeurons.push_back(Neuron(NumInputsPerNeuron));
}

NeuralNetwork::NeuralNetwork()
{
	m_NumInputs = 3;
	m_NumOutputs = 5;
	m_NumHiddenLayers = 1;
	m_NeuronsPerHiddenLayer = 4;

	CreateNet();

}

void NeuralNetwork::CreateNet()
{
	//create the layers of the network
	if (m_NumHiddenLayers > 0)
	{
		//create first hidden layer
		m_vecLayers.push_back(NeuronLayer(m_NeuronsPerHiddenLayer, m_NumInputs));

		for (int i = 0; i < m_NumHiddenLayers - 1; ++i)
		{

			m_vecLayers.push_back(NeuronLayer(m_NeuronsPerHiddenLayer, m_NeuronsPerHiddenLayer));
		}

		//create output layer
		m_vecLayers.push_back(NeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLayer));
	}

	else
	{
		//create output layer
		m_vecLayers.push_back(NeuronLayer(m_NumOutputs, m_NumInputs));
	}
}

vector<double> NeuralNetwork::GetWeights() const
{
	//this will hold the weights
	vector<double> weights;

	//for each layer
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j)
		{
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
			{
				weights.push_back(m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k]);
			}
		}
	}

	return weights;
}

void NeuralNetwork::PutWeights(vector<double> &weights)
{
	int cWeight = 0;

	//for each layer
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j)
		{
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
			{
				m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] = weights[cWeight++];
			}
		}
	}

	return;
}

//---------------------------------GetNumberOfWeights---------------------
//
//	returns the total number of weights needed for the net
//
//------------------------------------------------------------------------
int NeuralNetwork::GetNumberOfWeights() const
{
	int weights = 0;

	//for each layer
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i)
	{
		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j)
		{
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
				weights++;
		}
	}
	return weights;
}

//-------------------------------Update-----------------------------------
//
//	given an input vector this function calculates the output vector
//
//------------------------------------------------------------------------
vector<double> NeuralNetwork::update(vector<double> &inputs)
{
	//stores the resultant outputs from each layer
	vector<double> outputs;

	int cWeight = 0;

	//first check that we have the correct amount of inputs
	if (inputs.size() != m_NumInputs)
	{
		//just return an empty vector if incorrect.
		return outputs;
	}

	//For each layer....
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i)
	{
		if (i > 0)
		{
			inputs = outputs;
		}

		outputs.clear();

		cWeight = 0;

		//for each neuron sum the (inputs corresponding weights).Throw 
		//the total at our sigmoid function to get the output.
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j)
		{
			double netinput = 0;

			int	NumInputs = m_vecLayers[i].m_vecNeurons[j].m_NumInputs;

			//for each weight
			for (int k = 0; k < NumInputs - 1; ++k)
			{
				//sum the weights x inputs
				netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] *
					inputs[cWeight++];
			}

			//add in the bias
			netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[NumInputs - 1];

			//we can store the outputs from each layer as we generate them. 
			//The combined activation is first filtered through the sigmoid 
			//function
			outputs.push_back(Sigmoid(netinput, 1));

			cWeight = 0;
		}
	}

	return outputs;
}

//-------------------------------Sigmoid function-------------------------
//
//------------------------------------------------------------------------
double NeuralNetwork::Sigmoid(double netinput, double response)
{
	return (1 / (1 + exp(-netinput / response)));
	//return tanh(netinput);
}

void NeuralNetwork::mutateWeights()
{
	int cWeight = 0;

	//for each layer
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j)
		{
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k)
			{
				if (rand() % 100 == 1)
				{
					//std::cout << "Mutating weight" << std::endl;
					m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] += (double) mathRandom(-0.1f, 0.1f);
				}
			}
		}
	}

	return;
}
