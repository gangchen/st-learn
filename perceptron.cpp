#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stack>

using namespace std;
using namespace boost;

class slSample{
public:
	slSample(){};
	slSample(short int y, vector <double> x);
	short int getY(){return Y;};
	vector <double> getX(){return X;};
	void setY(short int y){Y = y;};
	void setX(vector <double> x){X = x;};
private:
	short int Y;
	vector <double> X;
};

slSample::slSample(short int y, vector <double> x){
	Y = y;
	X = x;
}

class slData{
public:
	slData(){};
	slData(string inputFilename);
	slSample getSample(int i){return samples[i];};
	vector <slSample> getSamples(){return samples;};
	int getnFeatures(){return nFeatures;};
private:
	vector <slSample> samples;
	int nSamples, nFeatures;
};

slData::slData(string inputFilename){
	ifstream inputFile(inputFilename.c_str());
	if(!inputFile){
		cerr << "Input File Error" << endl;
		exit(1);
	}
	nSamples = 0;
	string line;
	vector<string> fields;
	while(inputFile.good()){
		getline(inputFile, line);
		split(fields, line, is_any_of("\t"));
		vector<double> tmpX;
		for(vector<string>::iterator it = fields.begin()+1;
			it != fields.end(); it++){
			tmpX.push_back(atof(it->c_str()));
		}
		slSample tmpslSample = slSample(atoi(fields[0].c_str()), tmpX);
		samples.push_back(tmpslSample);
		nSamples++;
		nFeatures = tmpX.size();
	}
	inputFile.close();
}

class slPerceptron{
public:
	slPerceptron(slData d);
	void train();
	vector<double> getw() {return w;};
	double getb() {return b;};
	void setData(slData d);
	slData getData() {return trainData;};
private:
	vector<double> w;
	double b;
	slData trainData;
	short int sign(double n);
};

short int slPerceptron::sign(double n){
	if(n >= 0){
		return 1;
	}else{
		return -1;
	}
}

slPerceptron::slPerceptron(slData d){
	trainData = d;
	for(unsigned i = 0; i < trainData.getnFeatures(); i++){
		w.push_back(1);
	}
	b = 1;

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
					w[i] = 1 * curSample.getY()*curX[i] + w[i];
				}
				b = b + 1 * curSample.getY();
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