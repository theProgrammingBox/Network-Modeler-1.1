#pragma once
#include "Linear.h"

template <typename T>
class LinearLayer : public Layer<T>
{
public:
	LinearLayer(uint32_t outputSize);
	~LinearLayer() override;
	
	void init(Matrix<T>* input, Matrix<T>* inputGradient) override;
	void forward() override;
	void backward() override;
	void update(T scalar) override;
	void print() const override;

	Matrix<T>* weights;
	Matrix<T>* bias;
	Matrix<T>* weightsGradient;
	Matrix<T>* biasGradient;
};

template <typename T>
LinearLayer<T>::LinearLayer(uint32_t outputSize) : Layer<T>()
{
	bias = new Matrix<T>(1, outputSize);
	biasGradient = new Matrix<T>(1, outputSize);
	this->output = new Matrix<T>(1, outputSize);
	this->outputGradient = new Matrix<T>(1, outputSize);

	bias->fillRandom();
	biasGradient->zero();
	this->outputGradient->zero();
}

template <typename T>
LinearLayer<T>::~LinearLayer()
{
	delete weights;
	delete bias;
	delete weightsGradient;
	delete biasGradient;
	delete this->output;
	delete this->outputGradient;
}

template <typename T>
void LinearLayer<T>::init(Matrix<T>* input, Matrix<T>* inputGradient)
{
	this->input = input;
	this->inputGradient = inputGradient;
	weights = new Matrix<T>(input->cols, this->output->cols);
	weightsGradient = new Matrix<T>(input->cols, this->output->cols);

	this->inputGradient->fillRandom();
	weights->fillRandom();
	weightsGradient->zero();
}

template <typename T>
void LinearLayer<T>::forward()
{
	this->output->equalMatrixTimesMatrix(this->input, weights);
	this->output->add(bias);
}

template <typename T>
void LinearLayer<T>::backward()
{
	this->inputGradient->equalMatrixTimesMatrixTransposed(this->outputGradient, weights);
	weightsGradient->equalMatrixTransposedTimesMatrix(this->input, this->outputGradient);
}

template <typename T>
void LinearLayer<T>::update(T scalar)
{
	/*weightsGradient->times(scalar);
	this->outputGradient->times(scalar);
	weightsGradient->clamp(-1.0f, 1.0f);
	this->outputGradient->clamp(-1.0f, 1.0f);*/
	weights->add(weightsGradient, scalar, -1.0f, 1.0f);
	bias->add(this->outputGradient, scalar, -1.0f, 1.0f);
}

template <typename T>
void LinearLayer<T>::print() const
{
	cout << "LinearLayer" << endl;
	cout << "input:\n";
	this->input->print();
	cout << "inputGradient:\n";
	this->inputGradient->print();
	cout << "weights:\n";
	weights->print();
	cout << "weightsGradient:\n";
	weightsGradient->print();
	cout << "bias:\n";
	bias->print();
	cout << "biasGradient:\n";
	biasGradient->print();
	cout << "output:\n";
	this->output->print();
	cout << "outputGradient:\n";
	this->outputGradient->print();
}