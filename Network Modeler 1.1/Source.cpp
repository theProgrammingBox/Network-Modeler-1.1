#include "NetworkModeler.h"
#include "LinearLayer.h"

int main() {
	Matrix* input = new Matrix(new vector<int>{ 1, 2 });
	NetworkModeler networkModeler;
	networkModeler.addInput(input);
	networkModeler.addLayer(new LinearLayer(new Matrix(new vector<int>{ 1, 4 })));
	networkModeler.addLayer(new LinearLayer(new Matrix(new vector<int>{ 1, 1 })));
	Matrix* output = networkModeler.getOutput();
	
	networkModeler.printOverview();
	networkModeler.printParams();

	return 0;
}