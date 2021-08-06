#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include "Constant.h"
#include "Expense.h"
#include "Budget.h"
#include "Str.h"

using namespace std;

void WriteExp();
void monthlyReport();
void yearlyReport();
void budgetReport();
void setBudget();
void constUpdate();

const int SIZE = 5;
const int CATSIZE = 12;
const string KEYS[SIZE] = { "Income", "Rent", "Rent Insurance", "Electronics", "Health Insurance" };
const string CAT[CATSIZE] = {
    "utility bills (gas...): ", "medicine: ", "Groceries: ", "Household Supply: ", "restauration: ",
    "car expenses: ", "public Transportation: ", "Entertainment: ", "saving: ", "bank fees: ", "money sent to family: ",
    "miscellaneous: "
};


int main()
{
    int option;
    do {
        cout << "Select one from the following: " << endl;
        do {
            cout << "1.Write Expense\n2.Monthly Report\n3.Yearly Report\n4.Get Budget\n5.Set Budget\n6.Change Const. Values" << endl;
            cin >> option;
        
            if (option < 1 || option > 6) 
                cout << "ERROR: Please enter an integer between 1 to 6" << endl;
            else if (option == 1) {
                WriteExp();
            }
            else if (option == 2) {
                monthlyReport();
            }
            else if (option == 3) {
                yearlyReport();
            }
            else if (option == 4) {
                budgetReport();
            }
            else if (option == 5) {
                setBudget();
            }
            else {
                constUpdate();
            }

        } while (option < 1 || option > 5);

        cout << "Enter 7 to get back to main menu or else to quit" << endl;
        cin >> option;
        
        system("cls");
    } while (option == 7);
    cout << "Status: exit" << endl;

}


void WriteExp() {
    string date;
    double amount;
    Expense expense;
    Constant constant;
    vector<double> data;
    vector<double> constVals = constant.getData();    
    
    system("cls");
    if (constant.isConstSet()) {
            do {
                    cout << "Enter date of expense in format mm/yyyy: ";
                    cin >> date;

                    if (!STR.isDateValid(date)) {
                            cout << "ERROR: Please enter a valid date." << endl;
                    }

            } while (!STR.isDateValid(date));

            system("cls");
        if (expense.isDailyExpenses(date)) {
                for (int index = 0; index < constVals.size(); index++)
                        data.push_back(0.0);
        }
        else {
                for (int index = 0; index < constVals.size(); index++)
                        data.push_back(constVals[index]);
        }
        //Get the constant values first
        

        for (int index = 0; index < CATSIZE; index++) {
            do {
                cout << "Enter amount for " << CAT[index] << " $";
                cin >> amount;
                if (amount < 0) 
                    cout << "ERROR: Invalid input (negative number)" << endl;
                
            } while (amount < 0);
            data.push_back(amount);
        }
        system("cls");
        expense.writeExp(date, data);
    }
    else {
        cout << "Constant values are not set please them first." << endl;
        system("pause");
        constUpdate();
    }

}

void monthlyReport() {
    int count = 0;
    string date; 
    vector<double> data;

    system("cls");
    do {
        cout << "Enter the date of the expense (mm/yyyy): " << endl;
        cin >> date;

        if (!STR.isDateValid(date)) {
            cout  << "ERROR: Invalid date  " << endl;
        }
    } while (!STR.isDateValid(date));

    Expense expense(date);
    

    data = expense.getExpenses();

    if (!data.empty()) {
        system("cls");
        cout << "\tIrene Bessin - Monthly Expense " << date << endl << endl;
        cout << left << setw(20) << "Categories" << right << setw(20)
            << "Amount Spent" << endl;

        for (int index = 0; index < SIZE; index++) {
            cout << fixed << setprecision(2) << left << setw(25) << KEYS[index] 
                 << right << setw(7) << "$"<< left << setw(7) 
                 << data[count++] << endl;
        }

        for (int index = 0; count < data.size(); index++) {
            cout << fixed << setprecision(2) << left << setw(25) << CAT[index] 
                 << right << setw(7) << "$"<< left << setw(7) 
                 << data[count++] << endl;
        }

        cout << "_____________________________________________________________________" << endl;
        cout << fixed << setprecision(2) << "Total Expense: " << right << setw(17) << "$"
            << left << setw(7) << expense.getMTotal() << endl;
    }
    else {
        cout << "Data for date: " << date << " was not found." << endl;
        cout << "You need to set the data before accessing it." << endl;
    }

}

void yearlyReport() {
    string date;
    int count = 0;
    vector<double> data;

    do {
        cout << "Enter the date for the yearly report(yyyy): " << endl;
        cin >> date;

        if (!STR.isValidYear(date)) {
            cout << "ERROR: Please enter a valid year" << endl;
        }
    } while (!STR.isValidYear(date));

    Expense expenses;
    expenses.computeTotal(date);
    data = expenses.getTotal();

    if (!data.empty()) {
        system("cls");
        cout << "\tIrene Bessin - Yearly Expense " << date << endl << endl;
        cout << left << setw(20) << "Categories" << right << setw(20)
            << "Amount Spent" << endl;

        for (int index = 0; index < SIZE; index++) {
            cout << fixed << setprecision(2) << left << setw(25) << KEYS[index] 
                 << right << setw(7) << "$" << left << setw(7) 
                 << data[count++] << endl;
        }

        for (int index = 0; count < data.size(); index++) {
            cout << fixed << setprecision(2) << left << setw(25) << CAT[index]
                 << right << setw(7) << "$" << left << setw(7) 
                 << data[count++] << endl;
        }

        cout << "_____________________________________________________________________" << endl;
        cout << fixed << setprecision(2) << "Total Expense: " << right << setw(17) << "$"
            << left << setw(7) << expenses.getYTotal() << endl;
    }
    else {
        cout << "Data for year: " << date << " was not found." << endl;
        cout << "You need to set the data before accessing it." << endl;
    }

}

void budgetReport() {
    string date;
    int count = 4;

    do {
        cout << "Enter the date for the budget (mm/yyyy): " << endl;
        cin >> date;

        if (!STR.isDateValid(date))
            cout << "Please enter a valid date " << endl;
    } while (!STR.isDateValid(date));

    Budget budget(date);
    Expense exp(date);
    vector<double> expData = exp.getExpenses();
    vector<double> data = budget.getBudget();

    if (budget.isSet()) {
        system("cls");
        cout << "\tIrene Bessin - Buget Expense " << date << endl << endl;
        cout << left << setw(20) << "Categories" << right << setw(20)
             << "Amount Spent" << right << setw(20) << "Budget " 
             << right << setw(20) <<  "Percent" << endl;

        for (int index = 0; index < CATSIZE; index++) {
            cout << fixed << setprecision(2) << left << setw(26) << CAT[index] << right << setw(7) << "$" 
                 << left << setw(7) << expData[count++];
            cout << fixed << setprecision(2) << right << setw(15) << "$" << left << setw(15) << data[index]
                 << right << setw(7) << budget.perct(expData[count - 1], data[index]) << "%" << endl;
        }

        cout << "___________________________________________________________________________________" << endl;
        cout << fixed << setprecision(2) << "Total Budget: " << right << setw(18) << "$"
             << left << setw(7) << budget.getExpTotal(expData) << right << setw(15) << "$"
             << left << setw(15) << budget.getTotal() << right << setw(8) 
             << budget.perct(budget.getExpTotal(expData), budget.getTotal()) << "%" << endl;
    }
    else {
        cout << "Data for year: " << date << " was not found." << endl;
        cout << "You need to set the data before accessing it." << endl;
    }


}

void setBudget() {
    string date;
    double amount;
    vector<double> data;

    do {
        cout << "Enter the date for the budget you want to set (mm/yyyy): " << endl;
        cin >> date;

        if (!STR.isDateValid(date))
            cout << "Please enter a valid date " << endl;
    } while (!STR.isDateValid(date));

    Budget budget(date);

    for (int index = 0; index < CATSIZE; index++) {
        do {
            cout << "Enter amount for " << CAT[index] << " $";
            cin >> amount;

            if (amount < 0)
                cout << "ERROR: Invalid input (negative number)" << endl;
        } while (amount < 0);
        data.push_back(amount);
    }

    budget.setBudget(data);
}

void constUpdate() {
    Str str;
    int option;
    double input;
    Constant constant;


    do {
        system("cls");
        cout << "Select one from the folowing you would like to change: " << endl;
        do {
            cout << "1.Income\n2.Rent\n3.Rent Insurance\n4.Utilities (Phone, cable, etc...)\n5.Health Insurance" << endl;
            cout << "6.Electronics" << endl;
            cin >> option;
       
            if (option < 1 || option > 6)
                cout << "Pleases enter number between 1 amd 6" << endl;
            else if (option == 1) {
                cout << "Enter value for income: ";
                cin >> input;
                constant.changeVal(KEYS[option - 1], input);
            }
            else if (option == 2) {
                cout << "Enter value for rent: ";
                cin >> input;
                constant.changeVal(KEYS[option - 1], input);
            }
            else if (option == 3) {
                cout << "Enter value for rent insurance: ";
                cin >> input;
                constant.changeVal(KEYS[option - 1], input);
            }
            else if (option == 4) {
                cout << "Enter value for health insurance: ";
                cin >> input;
                constant.changeVal(KEYS[option - 1], input);
            }
            else {
                cout << "Enter value for Electronics(Phone, cable, etc): ";
                cin >> input;
                constant.changeVal(KEYS[option - 1], input);
            }
        } while (option < 1 || option > 5);

        cout << "Enter 6 to change category or else to quit: ";
        cin >> option;
        
        system("cls");
    } while (option == 6);

    constant.update(KEYS, SIZE);
    cout << "Data Updated" << endl;
}

