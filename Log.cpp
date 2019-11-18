#include "Log.h"
#include <fstream>
#include <iostream>

using namespace std;

void Log::clear() {
	logList.clear();
}
void Log::logOutputs(){
	logCommand = false;
	logOutput = true;
}
void Log::logCommands(){
	logCommand = true;
	logOutput = false;
}
void Log::logBoth(){
	logCommand = true;
	logOutput = true;
}
void Log::stopLogging(){
	logCommand = false;
	logOutput = false;
}
void Log::addToLog(string logMessage, bool command){
	if(command) {
		if(logCommand)
			logList.push_back(logMessage);	
	} else {
		if(logOutput)
			logList.push_back(logMessage);	
	}
	
}

void  Log::addToLog(vector<string> logMessage) {
	if(logOutput) {
		for (auto it = logMessage.begin(); it != logMessage.end(); it++) 
   	 		logList.push_back(*it);	
	}

	
}

void Log::save(string fileName){
	ofstream file(fileName, ofstream::out);  

	if(!file){
		cout << "ERROR: could not open file " << fileName << "  ...exiting\n";
		return;
	}

	for(size_t i=0; i<logList.size(); ++i) 
    	file << logList[i] << endl; 

    file.close();

}

vector<string>& Log::getLog(){
	return logList;
}