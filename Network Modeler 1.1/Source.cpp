#include "NetworkModeler.h"
#include "LinearLayer.h"

template <typename T>
struct Matrix1D
{
	uint32_t elements;
	T* data;
	
	Matrix1D() : elements(0), data(nullptr) {}
	Matrix1D(uint32_t elements) : elements(elements), data(new T[elements]) {}
	Matrix1D(const Matrix1D& matrix) : elements(matrix.elements), data(new T[elements]) { memcpy(data, matrix.data, elements * sizeof(T)); }
	~Matrix1D() { delete[] data; }
	
	Matrix1D& operator=(const Matrix1D& matrix) { elements = matrix.elements; delete[] data; data = new T[elements]; memcpy(data, matrix.data, elements * sizeof(T)); return *this; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	
	T operator*(const Matrix1D& matrix) const { T result = 0; for (int i = 0; i < elements; i++) result += data[i] * matrix.data[i]; return result; }
	Matrix1D operator+(const Matrix1D& matrix) const { Matrix1D result(elements); for (int i = 0; i < elements; i++) result.data[i] = data[i] + matrix.data[i]; return result; }
	
	const string str() const { string result = "["; for (int i = 0; i < elements; i++) result += to_string(data[i]) + (i < elements - 1 ? ", " : "]");; return result; }
	friend ostream& operator<<(ostream& os, const Matrix1D& matrix) { os << matrix.str(); return os; }
	
	void save(const string& fileName) const { ofstream file(fileName, ios::binary); save(file); file.close(); }
	void save(ofstream& file) const { file.write((char*)&elements, sizeof(int)); file.write((char*)data, elements * sizeof(T)); }
	
	void randomize() { for (int i = 0; i < elements; i++) data[i] = random.normalRand(); }
	void zero() { memset(data, 0, elements * sizeof(T)); }
};

template <typename T>
struct Matrix2D
{
	uint32_t elements, features, size;
	T* data;
	
	Matrix2D() : elements(0), features(0), size(0), data(nullptr) {}
	Matrix2D(uint32_t elements, uint32_t features) : elements(elements), features(features), size(elements* features), data(new T[size]) {}
	Matrix2D(const Matrix2D& matrix) : elements(matrix.elements), features(matrix.features), size(matrix.size), data(new T[size]) { memcpy(data, matrix.data, size * sizeof(T)); }
	~Matrix2D() { delete[] data; }
	
	Matrix2D& operator=(const Matrix2D& matrix) { elements = matrix.elements; features = matrix.features; size = matrix.size; delete[] data; data = new T[size]; memcpy(data, matrix.data, size * sizeof(T)); return *this; }
	T& operator()(int element, int feature) { return data[element * features + feature]; }
	const T& operator()(int element, int feature) const { return data[element * features + feature]; }
	
	Matrix1D<T> operator[](int element) const { Matrix1D<T> result(features); for (int i = 0; i < features; i++) result.data[i] = data[element * features + i]; return result; }
	
	Matrix1D<T> operator*(const Matrix1D<T>& matrix) const { Matrix1D<T> result(elements); for (int i = 0; i < elements; i++) result.data[i] = (*this)[i] * matrix; return result; }
	Matrix2D operator+(const Matrix2D& matrix) const { Matrix2D result(elements, features); for (int i = 0; i < size; i++) result.data[i] = data[i] + matrix.data[i]; return result; }
	
	const string str() const { string result = "["; for (int i = 0; i < elements; i++) result += (*this)[i].str() + (i < elements - 1 ? ",\n" : "]"); return result; }
	friend ostream& operator<<(ostream& os, const Matrix2D& matrix) { os << matrix.str(); return os; }
	
	void save(const string& fileName) const { ofstream file(fileName, ios::binary); save(file); file.close(); }
	void save(ofstream& file) const { file.write((char*)&elements, sizeof(int)); file.write((char*)&features, sizeof(int)); file.write((char*)data, size * sizeof(T)); }
	
	void randomize() { for (int i = 0; i < size; i++) data[i] = random.normalRand(); }
	void zero() { memset(data, 0, size * sizeof(T)); }
};

int main()
{
	Matrix1D<float> matrix(10);
	matrix.randomize();
	cout << matrix << "\n\n";
	Matrix1D<float> matrix2(10);
	matrix2.randomize();
	cout << matrix2 << "\n\n";
	Matrix1D<float> matrix3 = matrix + matrix2;
	cout << matrix3 << "\n\n";

	float value = matrix * matrix2;
	cout << value << "\n\n";

	Matrix2D<float> matrix4(10, 10);
	matrix4.randomize();
	cout << matrix4 << "\n\n";
	Matrix2D<float> matrix5(10, 10);
	matrix5.randomize();
	cout << matrix5 << "\n\n";
	Matrix2D<float> matrix6 = matrix4 + matrix5;
	cout << matrix6 << "\n\n";
	
	Matrix1D<float> matrix7 = matrix4 * matrix;
	cout << matrix7 << "\n\n";

	return 0;
}