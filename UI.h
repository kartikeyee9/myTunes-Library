

#ifndef UI_H
#define UI_H
#include <vector> 
#include <string>
using namespace std;


class UI
{
  public:
    void promptForStr(string, string&);
    void printMessage(string);
    void printParsedCommand(vector<string>&);
};

#endif
