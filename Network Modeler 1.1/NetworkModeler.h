#pragma once
#include "Linear.h"

template <typename T>
class NetworkModeler
{
public:
	NetworkModeler();
	~NetworkModeler();

	void setIO(Matrix<T>* input, Matrix<T>* target);
	void addLayer(Layer<T>* layer);
	Matrix<T>* getOutput() const;
	void init();
	void forward();
	void backward();
	void update(T scalar);
	void print() const;
	
	vector<Layer<T>*> layers;
	Matrix<T>* input;
	Matrix<T>* inputGradient;
	// input bias?
	Matrix<T>* output;
	Matrix<T>* target;
};

template <typename T>
NetworkModeler<T>::NetworkModeler() : input(nullptr), inputGradient(nullptr), output(nullptr), target(nullptr)
{
}

template <typename T>
NetworkModeler<T>::~NetworkModeler()
{
}

template <typename T>
void NetworkModeler<T>::setIO(Matrix<T>* input, Matrix<T>* target)
{
	this->input = input;
	this->target = target;
	inputGradient = new Matrix<T>(input->rows, input->cols);
}

template <typename T>
void NetworkModeler<T>::addLayer(Layer<T>* layer)
{
	layers.push_back(layer);
}

template <typename T>
Matrix<T>* NetworkModeler<T>::getOutput() const
{
	return layers[layers.size() - 1]->output;
}

template <typename T>
void NetworkModeler<T>::init()
{
	for (int i = 0; i < layers.size(); i++)
	{
		if (i == 0)
		{
			layers[i]->init(input, inputGradient);
		}
		else
		{
			layers[i]->init(layers[i - 1]->output, layers[i - 1]->outputGradient);
		}
	}
	output = layers[layers.size() - 1]->output;
}

template <typename T>
void NetworkModeler<T>::forward()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->forward();
	}
}

template <typename T>
void NetworkModeler<T>::backward()
{
	layers[layers.size() - 1]->outputGradient->equalMatrixMinusMatrix(target, output);
	for (int i = layers.size() - 1; i >= 0; i--)
	{
		layers[i]->backward();
	}
}

template <typename T>
void NetworkModeler<T>::update(T scalar)
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->update(scalar);
	}
}

template <typename T>
void NetworkModeler<T>::print() const
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->print();
	}
}