#pragma once
#include "Header.h"

template <typename T>
struct Matrix
{
	T* data;
	uint32_t rows;
	uint32_t cols;

	Matrix() : data(nullptr), rows(0), cols(0) {}
	Matrix(uint32_t rows, uint32_t cols) : data(new T[rows * cols]), rows(rows), cols(cols) {}
	Matrix(Matrix&& other) noexcept : data(other.data), rows(other.rows), cols(other.cols) {}
	~Matrix() { delete[] data; }

	T& operator()(uint32_t row, uint32_t col) { return data[row * cols + col]; }
	const T& operator()(uint32_t row, uint32_t col) const { return data[row * cols + col]; }
	void add(const Matrix* other) { for (uint32_t i = rows * cols; i--;) data[i] += other->data[i]; }
	void times(const T scalar) { for (uint32_t i = rows * cols; i--;) data[i] *= scalar; }
	void equalMatrixMinusMatrix(const Matrix* other1, const Matrix* other2) { for (uint32_t i = rows * cols; i--;) data[i] = other1->data[i] - other2->data[i]; }
	void equalMatrixTimesMatrix(const Matrix* other1, const Matrix* other2)
	{
		for (uint32_t i = 0; i < rows; i++)
		{
			for (uint32_t j = 0; j < cols; j++)
			{
				T sum = 0;
				for (uint32_t k = 0; k < other1->cols; k++)
				{
					sum += other1->data[i * other1->cols + k] * other2->data[k * other2->cols + j];
				}
				data[i * cols + j] = sum;
			}
		}
	}
	void equalMatrixTimesMatrixTransposed(const Matrix* other1, const Matrix* other2)
	{
		for (uint32_t i = 0; i < rows; i++)
		{
			for (uint32_t j = 0; j < cols; j++)
			{
				T sum = 0;
				for (uint32_t k = 0; k < other1->cols; k++)
				{
					sum += other1->data[i * other1->cols + k] * other2->data[j * other2->cols + k];
				}
				data[i * cols + j] = sum;
			}
		}
	}
	void equalMatrixTransposedTimesMatrix(const Matrix* other1, const Matrix* other2)
	{
		for (uint32_t i = 0; i < rows; i++)
		{
			for (uint32_t j = 0; j < cols; j++)
			{
				T sum = 0;
				for (uint32_t k = 0; k < other1->rows; k++)
				{
					sum += other1->data[k * other1->cols + i] * other2->data[k * other2->cols + j];
				}
				data[i * cols + j] = sum;
			}
		}
	}

	void print() const
	{
		for (uint32_t i = 0; i < rows; i++)
		{
			for (uint32_t j = 0; j < cols; j++)
			{
				cout << data[i * cols + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void zero() { memset(data, 0, rows * cols * sizeof(T)); }
	void fillRandom() { for (uint32_t i = rows * cols; i--;) data[i] = random.normalRand(); }
	void clamp(T s, T b) { for (uint32_t i = rows * cols; i--;) data[i] = max(s, min(b, data[i])); }
	template<typename F>
	void equalAlteredMatrix(F func, const Matrix* other) { for (uint32_t i = rows * cols; i--;) data[i] = func(other->data[i]); }
	template<typename F>
	void equalAlteredMatrixGradient(F func, const Matrix* input, const Matrix* gradient) { for (uint32_t i = rows * cols; i--;) data[i] = func(input->data[i], gradient->data[i]); }

	/*void save(ofstream& file) const
	{
		file.write((char*)&rows, sizeof(uint32_t));
		file.write((char*)&cols, sizeof(uint32_t));
		file.write((char*)&transposed, sizeof(bool));
		file.write((char*)data, rows * cols * sizeof(T));
	}

	void load(ifstream& file)
	{
		file.read((char*)&rows, sizeof(uint32_t));
		file.read((char*)&cols, sizeof(uint32_t));
		file.read((char*)&transposed, sizeof(bool));
		data = new T[rows * cols];
		file.read((char*)data, rows * cols * sizeof(T));
	}*/
};