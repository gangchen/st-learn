#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "slData.h"


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

#endif