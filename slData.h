#ifndef SLDATA_H
#define SLDATA_H
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

#endif
