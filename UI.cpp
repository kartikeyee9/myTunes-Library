
#include <iostream>
#include <iomanip>
#include <string>
#include "UI.h"
#include <vector> 
using namespace std;


void UI::promptForStr(string prompt, string& str)
{
  cout << prompt << ": ";
  getline(cin, str);
}

void UI::printMessage(string message)
{
  cout << message << endl;
}



void UI::printParsedCommand(vector<string>& parsed) {
  for (auto it = parsed.begin(); it != parsed.end(); it++) 
    cout << *it << endl; 
}

