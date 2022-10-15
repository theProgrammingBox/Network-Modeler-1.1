#include "NetworkModeler.h"
#include "LinearLayer.h"

template <typename T>
struct Matrix1D
{
	int elements;
	T* data;
	Matrix1D() : elements(0), data(nullptr) {}
	Matrix1D(int elements) : elements(elements), data(new T[elements]) {}
	Matrix1D(const Matrix1D& matrix) : elements(matrix.elements), data(new T[elements]) { memcpy(data, matrix.data, elements * sizeof(T)); }
	~Matrix1D() { delete[] data; }
	Matrix1D& operator=(const Matrix1D& matrix) { elements = matrix.elements; delete[] data; data = new T[elements]; memcpy(data, matrix.data, elements * sizeof(T)); return *this; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	T dot(const Matrix1D& matrix) const { T result = 0; for (int i = 0; i < elements; i++) result += data[i] * matrix.data[i]; return result; }
	Matrix1D& operator+=(const Matrix1D& matrix) { for (int i = 0; i < elements; i++) data[i] += matrix.data[i]; return *this; }
	Matrix1D& operator-=(const Matrix1D& matrix) { for (int i = 0; i < elements; i++) data[i] -= matrix.data[i]; return *this; }
	Matrix1D& operator*=(const Matrix1D& matrix) { for (int i = 0; i < elements; i++) data[i] *= matrix.data[i]; return *this; }
	Matrix1D& operator/=(const Matrix1D& matrix) { for (int i = 0; i < elements; i++) data[i] /= matrix.data[i]; return *this; }
	Matrix1D& operator+=(const T& value) { for (int i = 0; i < elements; i++) data[i] += value; return *this; }
	Matrix1D& operator-=(const T& value) { for (int i = 0; i < elements; i++) data[i] -= value; return *this; }
	Matrix1D& operator*=(const T& value) { for (int i = 0; i < elements; i++) data[i] *= value; return *this; }
	Matrix1D& operator/=(const T& value) { for (int i = 0; i < elements; i++) data[i] /= value; return *this; }
	Matrix1D operator+(const Matrix1D& matrix) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] + matrix.data[i]; return result; }
	Matrix1D operator-(const Matrix1D& matrix) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] - matrix.data[i]; return result; }
	Matrix1D operator*(const Matrix1D& matrix) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] * matrix.data[i]; return result; }
	Matrix1D operator/(const Matrix1D& matrix) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] / matrix.data[i]; return result; }
	Matrix1D operator+(const T& value) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] + value; return result; }
	Matrix1D operator-(const T& value) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] - value; return result; }
	Matrix1D operator*(const T& value) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] * value; return result; }
	Matrix1D operator/(const T& value) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] / value; return result; }
	const string str() const { string result = "["; for (int i = 0; i < elements; i++) result += to_string(data[i]) + (i < elements - 1 ? ", " : ""); result += "]"; return result; }
	friend ostream& operator<<(ostream& os, const Matrix1D& matrix) { os << matrix.str(); return os; }
	operator Matrix1D<float>() const { Matrix1D<float> result(elements); for (int i = 0; i < elements; i++) result.data[i] = (float)data[i]; return result; }
	operator Matrix1D<double>() const { Matrix1D<double> result(elements); for (int i = 0; i < elements; i++) result.data[i] = (double)data[i]; return result; }
	void save(const string& fileName) const { ofstream file(fileName, ios::binary); save(file); file.close(); }
	void save(ofstream& file) const { file.write((char*)&elements, sizeof(int)); file.write((char*)data, elements * sizeof(T)); }
	void randomize() { for (int i = 0; i < elements; i++) data[i] = random.normalRand(); }
	void zero() { memset(data, 0, elements * sizeof(T)); }
};

int main()
{
	Matrix1D<float> matrix(10);
	matrix.randomize();
	cout << matrix << endl;
	Matrix1D<float> matrix2(10);
	matrix2.randomize();
	cout << matrix2 << endl;
	Matrix1D<float> matrix3 = matrix + matrix2;
	cout << matrix3 << endl;

	float value = matrix.dot(matrix2);
	cout << value << endl;

	return 0;
}