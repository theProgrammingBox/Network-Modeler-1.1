#include "LinearLayer.h"
#include "ActivationLayer.h"
#include "NetworkModeler.h"

int main()
{
	auto leakyRelu = [](float x) { return x * (1.0f - (x < 0.0f) * 0.9f); };
	auto leakyReluGradient = [](float x, float y) { return y * (1.0f - (x < 0.0f) * 0.9f); };
	auto relu = [](float x) { return x * (x > 0.0f); };
	auto reluGradient = [](float x, float y) { return y * (x > 0.0f); };
	auto linearTanh = [](float x) { return (x > 1) - (x < -1) + x * (x <= 1 && x >= -1); };
	auto linearTanhGradient = [](float x, float y) { return y * (x <= 1 && x >= -1); };
	
	uint32_t inputs = 2;
	uint32_t outputs = 3;
	float learningRate = 0.01f;

	NetworkModeler<float> modeler;
	Matrix<float>* input = new Matrix<float>(1, inputs);
	Matrix<float>* target = new Matrix<float>(1, outputs);
	Matrix<float>* output;

	modeler.setIO(input, target);
	modeler.addLayer(new LinearLayer<float>(8));
	modeler.addLayer(new ActivationLayer<float>(linearTanh, linearTanhGradient));
	modeler.addLayer(new LinearLayer<float>(16));
	modeler.addLayer(new ActivationLayer<float>(linearTanh, linearTanhGradient));
	modeler.addLayer(new LinearLayer<float>(8));
	modeler.addLayer(new ActivationLayer<float>(linearTanh, linearTanhGradient));
	modeler.addLayer(new LinearLayer<float>(outputs));
	output = modeler.getOutput();
	modeler.init();
	
	int iter = 100000;
	while (iter--)
	{
		input->fillRandom();
		for (int i = 0; i < outputs; i++)
			(*target)(0, i) = (*input)(0, 0) * (i * -1.5 + 0.4) + (*input)(0, 1) * (i * 0.3 - 1.1) - 0.7 + ((*input)(0, 0) > 0) * 1.3;

		modeler.forward();
		modeler.backward();
		modeler.update(learningRate);
	}

	modeler.print();
	cout << "target:\n";
	target->print();

	return 0;
}