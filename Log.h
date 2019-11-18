

#ifndef LOG_H
#define LOG_H
#include <vector> 
#include <string>
using namespace std;


class Log
{
  public:
    void clear();
    void logOutputs();
    void logCommands();
    void logBoth();
    void stopLogging();
    void addToLog(string logMessage, bool command);
    void addToLog(vector<string> logMessage);
    void save(string fileName);
    vector<string>& getLog();

  private:
   	vector<string> logList;
   	bool logCommand = false;
   	bool logOutput = false;
};

#endif
