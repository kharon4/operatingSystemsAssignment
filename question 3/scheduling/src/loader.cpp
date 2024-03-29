#include "loader.h"


bool loadData(std::string filename, std::vector<process>& OUTvec) {
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	
	if (file.fail())return true;//error
	
	//resize outvec
	OUTvec.resize(0);

	//read the file
	while (!file.eof()) {
		process val;
		if (!file.eof())file >> val.processId;
		if (!file.eof())file >> val.arrivalTime;
		if (!file.eof())file >> val.burstTime;
		if (!file.eof())file >> val.priorityNo;
		val.originalBurstTime = val.burstTime;
		OUTvec.push_back(val);
	}
	return false;
}