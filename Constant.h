#ifndef CONSTANT_H
#define CONSTANT_H
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Str.h"
#include "LinkedList.h"

using namespace std;

class Constant{
	 private:
		  LinkedList linkedList;

	 public:
		  Constant() {
				Str str;
				string key, value;
				ifstream inputFile;

				inputFile.open("constant_value.csv", ios::in);
				if (inputFile) {
					 while (getline(inputFile, key, ':')) { 
						  getline(inputFile, value);	
						  linkedList.append(key, stod(value));
					 }
					 inputFile.close();
				} else {
					 cout << "Could not open file." << endl;
				}
		  }

		  //Change the value of a category using linked list
		  void changeVal(string key, double val) {
				linkedList.changeVal(key, val);	
		  }

		  //Update the constants by by writing data stored
		  //in the linked list in the constant_value.csv file
		  void update(const string list[], int size) {
				ofstream outputFile;

				outputFile.open("constant_value.csv", ios::out);
				if (outputFile) {
					 for (int index = 0; index < size; index++) {
						  outputFile << list[index] << ": " << linkedList.getVal(list[index]) << endl;
					 }
					 outputFile.close();
				} else {
					 cout << "Could not open file." << endl;
				}
				linkedList.deleteNodes();
		  }

		  //Check if the constant values are set
		  bool isConstSet() { return linkedList.size() != 0; }

		  //Return the constant values to be used to write expenses
		  vector<double> getData() { return linkedList.convert(); }
};

#endif