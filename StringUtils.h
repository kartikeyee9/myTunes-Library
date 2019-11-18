#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
using namespace std;


class StringUtils
{
  public:
    static string toUpperCase(string str);
    static string trim(string str);
    static bool startsWith(string str, string prefix);
    static bool endsWith(string str, string suffix);
    static string toString(bool);
    static string toTitleCase(string);
};

#endif
