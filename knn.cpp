#include "slData.h"

class knn{
public:
	knn(slData d);
	void train();
	int predict(slSample test);
private:
	slData trainData;
	string distMethod, classMethod;
	int k;

	void construt(slData d, int k, string distMethod, string classMethod);
	double Ldistance(slSample s1, slSample s2);// L_p distance
	double Edistance(slSample s1, slSample s2);// Euclidean distance
	double Mdistance(slSample s1, slSample s2);// manhanttan distance

	int Vote(slSample test); //majority voting rule

	void kd(); // construct KD-tree

};


void knn::construct(slData d, int kvalue, string distM, string classM){
	trainData = d;

	if(kvalue > 0){
		k = kvalue;
	}else{
		cerr << "K value should bigger than 1" << endl;
		cerr << "K is set to 5" << endl;
		k = 5;
	}

	if(distM == "L" || distM == "E" || distM == "M"){
		distMethod = distM;
	}else{
		cerr << "The value of Distance Method parameter should be one of L, E, and M" << endl
		cerr << "L2 distance method will be used" << endl;
		distMethod = "L";
	}

	classMethod = "V";

}

