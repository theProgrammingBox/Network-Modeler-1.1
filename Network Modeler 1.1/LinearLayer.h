#pragma once
#include "Matrix.h"

template <typename T>
class LinearLayer
{
public:
	LinearLayer(uint32_t outputs);
	~LinearLayer();

	void init(uint32_t inputs);
	void forward(Matrix<T>& input);
	void backward(Matrix<T>& input, Matrix<T>& inputGradient);
	void update(T scalar);
	void save(ofstream& file);
	void load(ifstream& file);

	Matrix<T> weights;
	Matrix<T> weightsGradient;
	Matrix<T> bias;
	Matrix<T> output;
	Matrix<T> outputGradient;
	
	uint32_t outputs;
};

template <typename T>
LinearLayer<T>::LinearLayer(uint32_t outputs)
{
	this->outputs = outputs;
}

template <typename T>
LinearLayer<T>::~LinearLayer()
{
}

template <typename T>
void LinearLayer<T>::init(uint32_t inputs)
{
	weights = Matrix<T>(inputs, outputs);
	weightsGradient = Matrix<T>(inputs, outputs);
	bias = Matrix<T>(1, outputs);
	output = Matrix<T>(1, outputs);
	outputGradient = Matrix<T>(1, outputs);
	weights.fillRandom();
	weightsGradient.fill(0.0f);
	bias.fillRandom();
	outputGradient.fill(0.0f);
}

template <typename T>
void LinearLayer<T>::forward(Matrix<T>& input)
{
	output = input * weights + bias;
}

template <typename T>
void LinearLayer<T>::backward(Matrix<T>& input, Matrix<T>& inputGradient)
{
	input.transpose();
	weightsGradient += input * outputGradient;
	input.transpose();
	weightsGradient.transpose();
	inputGradient += outputGradient * weightsGradient;
	weightsGradient.transpose();
}

template <typename T>
void LinearLayer<T>::update(T scalar)
{
	weightsGradient *= scalar;
	weights += weightsGradient;
	
	outputGradient *= scalar;
	bias += outputGradient;

	float error = 0.0f;
	for (int i = 0; i < outputs; i++)
	{
		error += fabs(outputGradient(0, i));
	}
	cout << "Error: " << error << endl;
	
	weightsGradient.fill(0.0f);
	outputGradient.fill(0.0f);
}

template <typename T>
void LinearLayer<T>::save(ofstream& file)
{
	weights.save(file);
	bias.save(file);
}

template <typename T>
void LinearLayer<T>::load(ifstream& file)
{
	weights.load(file);
	bias.load(file);
}