#pragma once
#include "Matrix.h"

class Layer
{
public:
	Layer(Matrix* output) : output(output) {};
	virtual ~Layer() {};
	
	virtual void printOverview() = 0;
	virtual void printParams() = 0;
	virtual void initParams(vector<int>* inputDimensions, vector<int>* outputDimensions) = 0;
	Matrix* getOutput() const { return output; };

protected:
	Matrix* output;
};