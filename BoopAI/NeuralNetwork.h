/*******************************************************************
* Basic Feed Forward Neural Network Class
* ------------------------------------------------------------------
* Bobby Anguelov - takinginitiative.wordpress.com (2008)
* MSN & email: banguelov@cs.up.ac.za
********************************************************************/

#ifndef NNetwork
#define NNetwork

#include "dataReader.h"

class neuralNetworkTrainer;

class neuralNetwork
{
	//class members
	//--------------------------------------------------------------------------------------------
private:

	//number of neurons
	int nInput, nHidden, nOutput;

	//neurons
	std::vector<double> inputNeurons;
	std::vector<double> hiddenNeurons;
	std::vector<double> outputNeurons;

	//weights
	double** wInputHidden;
	double** wHiddenOutput;

	//Friends
	//--------------------------------------------------------------------------------------------
	friend neuralNetworkTrainer;

	//public methods
	//--------------------------------------------------------------------------------------------

public:

	//constructor & destructor
	neuralNetwork(int numInput, int numHidden, int numOutput);
	~neuralNetwork();

	//weight operations
	bool loadWeights(char* inputFilename);
	bool saveWeights(char* outputFilename);
	std::vector<double> getWeights();
	void setWeights(std::vector<double> weights);
	std::vector<double> feedForwardPattern(std::vector<double> inputs);
	//double getSetAccuracy(std::vector<dataEntry*>& set);
	//double getSetMSE(std::vector<dataEntry*>& set);

	//private methods
	//--------------------------------------------------------------------------------------------

private:

	void initializeWeights();
	inline double activationFunction(double x);
	inline int clampOutput(double x);
	void feedForward(std::vector<double> inputs);

};

#endif
