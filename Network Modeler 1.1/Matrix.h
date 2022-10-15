#pragma once
#include "Header.h"

class Matrix
{
public:
	Matrix(vector<int>* dimensions);
	~Matrix();

	void randomize();
	void printOverview();
	void printParams(int dimension = 0, int index = 0);

	vector<int>* getDimensions() const;

private:
	vector<int>* dimensions;
	int totalSize;
	float* values;
};

Matrix::Matrix(vector<int>* dimensions)
{
	this->dimensions = dimensions;
	totalSize = 1;
	for (int i = 0; i < dimensions->size(); i++)
	{
		totalSize *= dimensions->at(i);
	}
	values = new float[totalSize];
}

Matrix::~Matrix()
{
	delete dimensions;
	delete[] values;
}

void Matrix::randomize()
{
	for (int i = 0; i < totalSize; i++)
	{
		this->values[i] = random.normalRand();
	}
}

void Matrix::printOverview()
{
	cout << "[" << this->dimensions->at(0);
	for (int i = 1; i < this->dimensions->size(); i++)
	{
		cout << ", " << this->dimensions->at(i);
	}
	cout << "] matrix ";
}

void Matrix::printParams(int dimension, int index)
{
	if (dimension == this->dimensions->size() - 1)
	{
		for (int i = 0; i < this->dimensions->at(dimension); i++)
		{
			cout << this->values[index + i] << " ";
		}
	}
	else
	{
		if (this->dimensions->at(dimension) == 1)
		{
			printParams(dimension + 1, index);
		}
		else
		{
			for (int i = 0; i < this->dimensions->at(dimension); i++)
			{
				printParams(dimension + 1, index + i * this->dimensions->at(dimension + 1));
				cout << endl;
			}
		}
	}
}

vector<int>* Matrix::getDimensions() const
{
	return this->dimensions;
}