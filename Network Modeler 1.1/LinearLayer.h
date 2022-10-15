#pragma once
#include "Layer.h"

class LinearLayer : public Layer
{
public:
	LinearLayer(Matrix* output) : Layer(output) {};
	~LinearLayer();
	
	void printOverview() override;
	void printParams() override;
	void initParams(vector<int>* inputDimensions, vector<int>* outputDimensions) override;
	Matrix* forward(Matrix* input) override;
	
private:
	Matrix* weights;
	Matrix* biases;
};

LinearLayer::~LinearLayer()
{
	delete weights;
	delete biases;
}

void LinearLayer::printOverview()
{
	cout << "Linear layer with a ";
	output->printOverview();
	cout << "output" << endl;
}

void LinearLayer::printParams()
{
	cout << "Weights: ";
	weights->printOverview();
	cout << endl;
	weights->printParams();
	cout << endl;
	cout << "Biases: ";
	biases->printOverview();
	cout << endl;
	biases->printParams();
	cout << endl;
}

void LinearLayer::initParams(vector<int>* inputDimensions, vector<int>* outputDimensions)
{
	assert(inputDimensions->size() == 2);
	assert(outputDimensions->size() == 2);
	
	weights = new Matrix(new vector<int>{ inputDimensions->at(1), output->getDimensions()->at(1), inputDimensions->at(0), output->getDimensions()->at(0) });
	weights->randomize();
	biases = new Matrix(output->getDimensions());
	biases->randomize();
}

Matrix* LinearLayer::forward(Matrix* input)
{
	assert(input->getDimensions()->size() == 2);
	assert(input->getDimensions()->at(0) == weights->getDimensions()->at(2));
	assert(input->getDimensions()->at(1) == weights->getDimensions()->at(0));
	assert(output->getDimensions()->at(0) == weights->getDimensions()->at(3));
	assert(output->getDimensions()->at(1) == weights->getDimensions()->at(1));
	assert(output->getDimensions()->at(0) == biases->getDimensions()->at(0));
	assert(output->getDimensions()->at(1) == biases->getDimensions()->at(1));
	
	//use matrix =, *, + opperators
	//output = input * weights + biases
	*output = *input * *weights + *biases;

	return output;
}