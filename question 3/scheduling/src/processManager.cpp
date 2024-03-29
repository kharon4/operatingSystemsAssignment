#include "processManager.h"

processManager::processManager(scheduler* SC) {
	currentExecutingId = -1;
	sc = SC;
	currentTime = 0;
}

void processManager::update() {
	//deal with last executing task
	if (!(currentExecutingId < 0)) {
		//subtract from its burst Time
		readylist[currentExecutingId].burstTime--;
		if (readylist[currentExecutingId].burstTime == 0) {
			//add to completed process list
			completedProcess p;
			p.P = readylist[currentExecutingId];
			p.turnArroundTime = currentTime - p.P.arrivalTime;
			p.waitTime = p.turnArroundTime - p.P.originalBurstTime;
			completedProcessList.push_back(p);
			//remove from ready list
			for(long long i = currentExecutingId ; i < readylist.size()-1 ; ++i)
			readylist[i] = readylist[i + 1];
			readylist.pop_back();
		}
	}
	
	
	//update ready list
	for (size_t i = 0; i < processList.size();) {
		if (processList[i].arrivalTime == currentTime) {
			if (processList[i].burstTime != 0)
			readylist.push_back(processList[i]);
			processList[i] = processList[processList.size() - 1];
			processList.pop_back();
		}
		else {
			i++;
		}
	}

	//find current execution
	currentExecutingId = sc->getRunningID(readylist);

	//update time
	currentTime++;
}


bool processManager::getRunningProcess(process& OUTprocess) {
	if (currentExecutingId < 0)return true;//error
	OUTprocess = readylist[currentExecutingId];
	return false;
}

size_t processManager::getTime() {
	return currentTime - 1;
}

bool processManager::executionFinished() {
	if (processList.size() == 0 && readylist.size() == 0)return true;
	return false;
}