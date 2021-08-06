#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Str.h"

using namespace std;

const int CATEGORIES_SIZE = 17;

class File {
	 private:
		  string date;
		  string fileName;
		  vector<double> data;
		  vector<double> dataTotal;
		  
	 public:
		  File(string d) {
			this->date = d;
			for (int index = 0; index < CATEGORIES_SIZE; index++)
				dataTotal.push_back(0.0);
		  }

		  File(string d, string fn) {
			this->date = d;
			this->fileName = fn;

			for (int index = 0; index < CATEGORIES_SIZE; index++)
				dataTotal.push_back(0.0);
		  }

		  //Used to get data from budget and expense file
		  //Return list of data from file
		  vector<double> getBudgetData() {
				fstream inputFile;
				string line;
				vector<string> tokens;
				Str str;

				inputFile.open(this->fileName, ios::in);
				if (inputFile) {
					 cout << "Gathering data..." << endl;
					 while (getline(inputFile, line)) {
						  str.split(line, ',', tokens);

						  if (tokens[0] == date) {
							for (int index = 1; index < tokens.size(); index++)
								 data.push_back(stod(tokens[index]));
							break;
						  }
						  tokens.clear();
					 }
					 inputFile.close();
					 cout << "Complete" << endl;
				}
				else {
					 cout << "Could not open file." << endl;
				}					 
				return data;
		  }

		  vector<double> getExpenseData() {
			  fstream inputFile;
			  string line;
			  vector<string> tokens;
			  Str str;

			  inputFile.open(this->fileName, ios::in);
			  if (inputFile) {
				  cout << "Gathering data..." << endl;
				  while (getline(inputFile, line)) {
					  str.split(line, ',', tokens);

					  if (tokens[0] == date) {
						  for (int index = 1; index < tokens.size(); index++)
							  dataTotal[index - 1] += stod(tokens[index]);
					  }
					  tokens.clear();
				  }
				  inputFile.close();
				  cout << "Complete" << endl;
			  }
			  else {
				  cout << "Could not open file." << endl;
			  }
			  return dataTotal;
		  }
};


#endif