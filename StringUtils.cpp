#include <string>
#include "StringUtils.h"

using namespace std;

string StringUtils::toUpperCase(string str){
	string s;
	for(char & c : str){
		s.append(1,toupper(c));
	}
	return s;
}


string StringUtils::trim(string str){
	string trimmed = str;
	trimmed.erase(0, trimmed.find_first_not_of(' '));
	trimmed.erase(trimmed.find_last_not_of(' ') + 1);
	return trimmed;
}

bool StringUtils::startsWith(string str, string key){
	return str.find(key) == 0;
}

bool StringUtils::endsWith(string str, string key){
	if(key.size() > str.size())
		return false;

	 return 0 == str.compare(str.size()-key.size(), key.size(), key);
}

string StringUtils::toString(bool key){
	return key ? "true" : "false";
}

string StringUtils::toTitleCase(string str){
	string titleCase = str;

	for (int i = 0; i < titleCase.size(); ++i)
	{
		if(i == 0 || titleCase[i-1] == ' ')
			titleCase[i] = toupper(titleCase[i]);
		else
			titleCase[i] = tolower(titleCase[i]);
	}

	size_t iFirstSpace = str.find(' '); 
    if (iFirstSpace != string::npos) {
    	string firstPart = titleCase.substr(0,iFirstSpace);
    	string lastPart = titleCase.substr(iFirstSpace + 1, titleCase.size() - iFirstSpace);
    	if(firstPart == "The")
    		titleCase = lastPart + ", " + firstPart; 
	}


	return titleCase;

}

