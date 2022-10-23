#include "LinearLayer.h"
#include "ActivationLayer.h"
#include "NetworkModeler.h"

int main()
{
	/*int inputs = 2;
	int hidden = 8;
	int outputs = 3;
	float learningRate = 0.1f;
	float max = 1.0f;
	float min = -1.0f;

	auto leakyRelu = [](float x) { return x * (1.0f - (x < 0.0f) * 0.9f); };
	auto leakyReluGradient = [](float x, float y) { return y * (1.0f - (x < 0.0f) * 0.9f); };

	Matrix<float>* input = new Matrix<float>(1, inputs);
	Matrix<float>* inputGradient = new Matrix<float>(1, inputs);
	Matrix<float>* target = new Matrix<float>(1, outputs);

	Layer<float>* hiddenLayer = new LinearLayer<float>(hidden);
	hiddenLayer->init(input, inputGradient);

	Layer<float>* activationLayer = new ActivationLayer<float>(leakyRelu, leakyReluGradient);
	activationLayer->init(hiddenLayer->output, hiddenLayer->outputGradient);

	Layer<float>* hiddenLayer2 = new LinearLayer<float>(hidden);
	hiddenLayer2->init(activationLayer->output, activationLayer->outputGradient);

	Layer<float>* activationLayer2 = new ActivationLayer<float>(leakyRelu, leakyReluGradient);
	activationLayer2->init(hiddenLayer2->output, hiddenLayer2->outputGradient);

	Layer<float>* outputLayer = new LinearLayer<float>(outputs);
	outputLayer->init(activationLayer2->output, activationLayer2->outputGradient);

	int iter = 1000;
	while (iter--)
	{
		input->fillRandom();
		for (int i = 0; i < outputs; i++)
			(*target)(0, i) = (*input)(0, 0) * (i * -1.5 + 0.4) + (*input)(0, 1) * (i * 0.3 - 1.1) - 0.7 + ((*input)(0, 0) > 0) * 1.3;

		hiddenLayer->forward();
		activationLayer->forward();
		hiddenLayer2->forward();
		activationLayer2->forward();
		outputLayer->forward();

		outputLayer->outputGradient->equalMatrixMinusMatrix(target, outputLayer->output);
		outputLayer->backward();
		activationLayer2->backward();
		hiddenLayer2->backward();
		activationLayer->backward();
		hiddenLayer->backward();

		hiddenLayer->update(learningRate);
		activationLayer->update(learningRate);
		hiddenLayer2->update(learningRate);
		activationLayer2->update(learningRate);
		outputLayer->update(learningRate);
	}

	outputLayer->outputGradient->print();

	delete input;
	delete inputGradient;
	delete hiddenLayer;*/

	NetworkModeler<float> modeler;
	
	uint32_t inputs = 2;
	uint32_t outputs = 3;
	float learningRate = 0.01f;
	Matrix<float>* input = new Matrix<float>(1, inputs);
	Matrix<float>* target = new Matrix<float>(1, outputs);
	Matrix<float>* output;

	auto leakyRelu = [](float x) { return x * (1.0f - (x < 0.0f) * 0.9f); };
	auto leakyReluGradient = [](float x, float y) { return y * (1.0f - (x < 0.0f) * 0.9f); };

	modeler.setInput(input);
	modeler.setTarget(target);
	modeler.addLayer(new LinearLayer<float>(8));
	modeler.addLayer(new ActivationLayer<float>(leakyRelu, leakyReluGradient));
	modeler.addLayer(new LinearLayer<float>(16));
	modeler.addLayer(new ActivationLayer<float>(leakyRelu, leakyReluGradient));
	modeler.addLayer(new LinearLayer<float>(8));
	modeler.addLayer(new ActivationLayer<float>(leakyRelu, leakyReluGradient));/**/
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

	modeler.output->print();
	target->print();

	return 0;
}