#pragma once
#include "Layer.h"

class NetworkModeler
{
public:
	NetworkModeler() {};
	~NetworkModeler() {};

	void printOverview();
	void printParams();
	void addInput(Matrix* input);
	void addLayer(Layer* layer);
	Matrix* getOutput() const;
	void forward();
	
private:
	Matrix* input;
	vector<Layer*> layers;
};

void NetworkModeler::printOverview()
{
	cout << "Network modeler with a ";
	input->printOverview();
	cout << "input" << endl;
	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->printOverview();
	}
	cout << endl;
}

void NetworkModeler::printParams()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers.at(i)->printParams();
		cout << endl;
	}
}

void NetworkModeler::addInput(Matrix* input)
{
	this->input = input;
}

void NetworkModeler::addLayer(Layer* layer)
{
	layers.push_back(layer);
	if (layers.size() == 1)
	{
		layer->initParams(input->getDimensions(), layer->getOutput()->getDimensions());
	}
	else
	{
		layer->initParams(layers[layers.size() - 2]->getOutput()->getDimensions(), layer->getOutput()->getDimensions());
	}
}

Matrix* NetworkModeler::getOutput() const
{
	return layers[layers.size() - 1]->getOutput();
}

void NetworkModeler::forward()
{
	layers[0]->forward(input);
	for (int i = 1; i < layers.size(); i++)
	{
		layers[i]->forward(layers[i - 1]->getOutput());
	}
}