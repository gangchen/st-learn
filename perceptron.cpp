#include "slData.h"

using namespace std;
using namespace boost;

class slPerceptron{
public:
	slPerceptron(const slData d);
	slPerceptron(const slData d, double learnRate);
	void train();
	vector<double> getw() {return w;};
	double getb() {return b;};
	void setData(slData d){ trainData = d;};
	slData getData() {return trainData;};
private:
	vector<double> w;
	double b;
	slData trainData;
	short int sign(double n);
	double learnRate;
	void construct(const slData d, double learnRate);
};

short int slPerceptron::sign(double n){
	if(n >= 0){
		return 1;
	}else{
		return -1;
	}
}

void slPerceptron::construct(const slData d, double l){
	if(l > 0 && l <= 1){
		learnRate = l;
	}else{
		cerr << "Warning: Learn Rate is expected to bigger than 0 and not bigger than 1" << endl;
		cerr << "Learn Rate is set to 1." << endl;
		learnRate = 1;
	}

	setData(d);
	for(unsigned i = 0; i < trainData.getnFeatures(); i++){
		w.push_back(1);
	}
	b = 1;
}

slPerceptron::slPerceptron(const slData d){
	construct(d, 1);
}

slPerceptron::slPerceptron(const slData d, double l){
	construct(d, l);
}

void slPerceptron::train(){
	vector<slSample> samples = trainData.getSamples();
	stack <slSample> reSamples;
	for(vector<slSample>::iterator it = samples.begin();
		it != samples.end(); it++){
		reSamples.push(*it);
	}
	while(!reSamples.empty()){
		double ret = 0;
		slSample curSample = reSamples.top();
		reSamples.pop();
		while(ret <= 0){
			ret = 0;
			vector<double> curX = curSample.getX();
			for(int i = 0; i < curX.size();i++){
				ret += curX[i] * w[i];
			}
			ret = curSample.getY()*(ret + b);
			for(std::vector<double>::iterator tIt = w.begin();
				tIt != w.end(); tIt++)
				cout << *tIt << "\t";
			cout << b << "\t";
			cout << ret << endl;
			if(ret <= 0){
				for(int i = 0; i < w.size(); i++){
					w[i] = learnRate * curSample.getY()*curX[i] + w[i];
				}
				b = b + learnRate * curSample.getY();
				while ( ! reSamples.empty() ){
    				reSamples.pop();
				}
				for(vector<slSample>::iterator it = samples.begin();
					it != samples.end(); it++){
					reSamples.push(*it);
				}
			}
		}
		cout << "========================" << endl;
	}
}

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