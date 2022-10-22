#pragma once
#include "Matrix.h"

template <typename T>
class Layer
{
public:
	Layer() : input(nullptr), inputGradient(nullptr), output(nullptr), outputGradient(nullptr) {}
	virtual ~Layer() = default;

	virtual void init(Matrix<T>* input, Matrix<T>* inputGradient) = 0;
	virtual void forward() = 0;
	virtual void backward() = 0;
	virtual void update(T scalar) = 0;
	virtual void print() const = 0;

	Matrix<T>* input;
	Matrix<T>* inputGradient;
	Matrix<T>* output;
	Matrix<T>* outputGradient;
};