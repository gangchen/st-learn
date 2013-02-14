#include "slData.h"
#include "perceptron.h"

int main(int argc, char *argv[]){

	slData d = slData(argv[1]);
	slPerceptron p = slPerceptron(d);
	p.train();
	cout << "###################" << endl;
	cout << p.getb() << endl;

	int i = 1;
	std::vector<double> w = p.getw();
	for(vector<double>::iterator it = w.begin();
		it != w.end(); it++){
		cout << i++ <<":"<< *it << endl;
	}
	return 0;
}