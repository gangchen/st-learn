#include "slData.h"

using namespace std;
using namespace boost;

slSample::slSample(short int y, vector <double> x){
	Y = y;
	X = x;
}

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