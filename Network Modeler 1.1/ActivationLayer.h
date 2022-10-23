#pragma once
#include "Linear.h"

template <typename T>
class ActivationLayer : public Layer<T>
{
public:
	ActivationLayer(function<T(T)> activation, function<T(T, T)> activationGradient);
	~ActivationLayer() override;

	void init(Matrix<T>* input, Matrix<T>* inputGradient) override;
	void forward() override;
	void backward() override;
	void update(T scalar) override;
	void print() const override;

private:
	function<T(T)> activationFunction;
	function<T(T, T)> activationFunctionGradient;
};

template <typename T>
ActivationLayer<T>::ActivationLayer(function<T(T)> activation, function<T(T, T)> activationGradient) : Layer<T>()
{
	activationFunction = activation;
	activationFunctionGradient = activationGradient;
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
	this->output->equalAlteredMatrix(activationFunction, this->input);
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