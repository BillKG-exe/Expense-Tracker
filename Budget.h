#ifndef BUDGET_H
#define BUDGET_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "Str.h"
#include "File.h"

using namespace std;

const string FNAME = "budget.txt";

class Budget {
	 private:
		  string date;
		  vector<double> month;
		  vector<double> percent;

	 public:
		  Budget(string date) {
				this->date = date;
		  }

		  //Write in a file the budget data that user set 
		  void setBudget(vector<double> data) {
				ofstream outputFile;

				outputFile.open("budget.txt", ios::app);
				cout << "Setting Budget..." << endl;
				if (outputFile) {
					 outputFile << endl << this->date << ", ";
					 for (int index = 0; index < data.size() - 1; index++)
						  outputFile << fixed << setprecision(2) << data[index] << ", ";
					 outputFile << fixed << setprecision(2) << data[data.size() - 1];
					 outputFile.close();
					 cout << "Complete" << endl;
				}
				else {
					 cout << "Could not open file." << endl;
				}
		  }

		  //Return the set budget for the specified month
		  vector<double> getBudget() {
				File file(this->date, FNAME);
				this->month = file.getBudgetData();
				return this->month;
		  }

		  //Check if budget for specified date is set
		  bool isSet() {
				if (this->month.size() != 0)
					 return 1;
				else
					 return 0;
		  }

		  //Use to get the total sum of the budget
		  double getTotal() {
				double total = 0.0;
				for (int index = 0; index < month.size(); index++) 
					 total += month[index];
				return total;
		  }

		  
		  double getExpTotal(vector<double> data) {
				double total = 0.0;
				for (int index = 5; index < data.size(); index++)
					 total += data[index];
				return total;
		  }

		  
		  double perct(double exp, double bdg) { 
				if (bdg == 0)
					 return 0;
				else
					 return (exp / bdg) * 100; 
		  }
		  vector<double> getMonth() { return month; }
		  vector<double> getPerct() { return percent; }
};

#endif
