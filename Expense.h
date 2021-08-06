#ifndef EXPENSE_H
#define EXPENSE_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Str.h"
#include "File.h"

using namespace std;

const Str STR;
const string FILENAME = "expense.csv";

class Expense {
private:  
	 string date;
	 const int SIZE = 17;
	 vector<double> expenses;
	 vector<double> total;

public:
	 Expense() {
		  date = ""; 

		  for (int index = 0; index < SIZE; index++) 
				total.push_back(0.0);
		  
	 }

	 Expense(string date) {
		  this->date = date;

		  for (int index = 0; index < SIZE; index++) {
				total.push_back(0.0);
		  }
			
		  File file(this->date, FILENAME);
		  expenses = file.getExpenseData();
	 }

	 //Write expenses entered by the user in expense.csv file 
	 void writeExp(string date, vector<double> data) {
		  ofstream outputFile;

		  outputFile.open("expense.csv", ios::app);
		  cout << "Writing expenses..." << endl;
		  if (outputFile) {
				outputFile << endl << date << ", ";
				for (int index = 0; index < data.size() - 1; index++) 
					 outputFile << fixed << setprecision(2) << data[index] << ", ";
				outputFile << fixed << setprecision(2) << data[data.size() - 1];
				outputFile.close();
				cout << "Completed" << endl;
		  } else {
				cout << "Could not open file." << endl;
		  }
	 }

	 //Add 0's to constant value if it is a daily input
	 bool isDailyExpenses(string date) {
		 ifstream inputFile;
		 vector<string> tokens;
		 Str str;
		 string line;
		 bool date_exists;

		 inputFile.open("expense.csv", ios::in);
		 if (inputFile) {
			 while (getline(inputFile, line)) {
				 str.split(line, ',', tokens);
				 if (tokens[0] == date) {
					 tokens.clear();
					 inputFile.close();
					 return 1;
				 }
				 tokens.clear();
			 }
			 inputFile.close();
			 return 0;
		 }
		 else {
			 cout << "Could not open file." << endl;
			 return 0;
		 }
	 }

	 //Get year of date format mm/yyyy
	 string getYear(string date) {
		  vector<string> tokens;
		  STR.split(date, '/', tokens);
		  return tokens[1];
	 }

	 //Used to compute the total spent in each
	 //categories
	 void computeTotal(string year) {
		  string line;
		  fstream inputFile;
		  vector<string> tokens;

		  inputFile.open("expense.csv", ios::in);

		  if (inputFile) {
				while (getline(inputFile, line)) {
					 STR.split(line, ',', tokens);
					 if (tokens[0] == "date") {
						  tokens.clear();
						  continue;
					 }
					 else if (getYear(tokens[0]) == year) {
						  for (int index = 1; index < tokens.size(); index++) 
								total[index - 1] += stod(tokens[index]);
					 }
					 tokens.clear();
				}
				inputFile.close();
		  } else {
				cout << "Could not open file." << endl;
		  }
	 }

	 //Get total amount spent during this->month
	 //Return total spent
	 double getMTotal() {
		  double total = 0.0;

		  for (int index = 0; index < expenses.size(); index++) 
				total += expenses[index];
		  
		  return total;
	 }

	 //Get total spent during a specified year
	 //Return amuunt soent in year
	 double getYTotal() {
		  double total = 0.0;

		  for (int index = 0; index < this->total.size(); index++)
				total += this->total[index];

		  return total;
	 }

	 string getDate() { return date; }
	 vector<double> getExpenses() { return expenses; }
	 vector<double> getTotal() { return total; }
};

#endif