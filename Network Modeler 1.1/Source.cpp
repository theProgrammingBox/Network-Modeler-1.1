#include "NetworkModeler.h"
#include "LinearLayer.h"

int main() {
	/*Matrix* matrix = new Matrix(new vector<int>{ 2, 3, 4 });
	matrix->randomize();
	matrix->printOverview();
	cout << endl;
	matrix->printParams();*/

	/*LinearLayer layer{ new Matrix(new vector<int>{ 1, 4 }) };
	layer.printOverview();
	cout << endl;
	layer.printParams();*/

	NetworkModeler networkModeler;
	networkModeler.addInput(new Matrix(new vector<int>{ 1, 2 }));
	networkModeler.addLayer(new LinearLayer(new Matrix(new vector<int>{ 1, 4 })));
	networkModeler.printOverview();
	cout << endl;
	networkModeler.printParams();

	return 0;
}