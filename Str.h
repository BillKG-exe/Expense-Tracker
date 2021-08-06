#ifndef String_H
#define String_H
#include<iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

const int DATESIZE = 7;
const int YEARSIZE = 4;
const int DELIM = 2;

class Str {
public:
	 static void split(const string& s, char delim, vector<string>& tokens) {
		  int tokenStart = 0;
		  int delimPosition = s.find(delim);

		  while (delimPosition != string::npos)
		  {
				string tok = s.substr(tokenStart, delimPosition - tokenStart);

				tokens.push_back(tok);
				delimPosition++;

				tokenStart = delimPosition;

				delimPosition = s.find(delim, delimPosition);

				if (delimPosition == string::npos)
				{
					 string tok = s.substr(tokenStart, delimPosition - tokenStart);

					 tokens.push_back(tok);
				}
		  }
	 }

	 //Used to check validity of date format mm/yyyy
	 static bool isDateValid(string date) {
		  if (date.size() < DATESIZE || date.size() > DATESIZE)
				return false;
		  else if (date[DELIM] != '/')
				return false;
		  else
				return true;
	 }

	 //Used to check the validity of the year (yyyy)
	 static bool isValidYear(string date) {
		  bool check = all_of(date.begin(), date.end(), isdigit);
		  if (date.size() < YEARSIZE || date.size() > YEARSIZE)
				return false;
		  else if (!check)
				return false;
		  else
				return true;
	 }
};

#endif