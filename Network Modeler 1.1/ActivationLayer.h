#pragma once
#include "Linear.h"

template <typename T>
class ActivationLayer : public Layer<T>
{
public:
	template <typename F>
	ActivationLayer(F&& activationFunction, F&& activationFunctionGradient);
	~ActivationLayer() override;

	void init(Matrix<T>* input, Matrix<T>* inputGradient) override;
	void forward() override;
	void backward() override;
	void update(T scalar) override;
	void print() const override;

private:
	T(*activationFunction)(T);
	T(*activationFunctionGradient)(T);
};

template <typename T>
template <typename F>
ActivationLayer<T>::ActivationLayer(F&& activationFunction, F&& activationFunctionGradient) : Layer<T>()
{
	this->activationFunction = activationFunction;
	this->activationFunctionGradient = activationFunctionGradient;
}

template <typename T>
ActivationLayer<T>::~ActivationLayer()
{
}

template <typename T>
void ActivationLayer<T>::init(Matrix<T>* input, Matrix<T>* inputGradient)
{
	this->input = input;
	this->inputGradient = inputGradient;
	this->output = new Matrix<T>(input->rows, input->cols);
	this->outputGradient = new Matrix<T>(input->rows, input->cols);
}

template <typename T>
void ActivationLayer<T>::forward()
{
	output->equalAlteredMatrix(activationFunction, input);
}

template <typename T>
void ActivationLayer<T>::backward()
{
	this->inputGradient->equalAlteredMatrixGradient(activationFunctionGradient, this->input, this->outputGradient);
}

template <typename T>
void ActivationLayer<T>::update(T scalar)
{
}

template <typename T>
void ActivationLayer<T>::print() const
{
}