#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Expense {
    string category;
    string description;
    float amount;
    struct {
        int day, month, year;
    } date;
};

void addExpense(vector<Expense> &expenses, float &totalSpent);
void viewExpenses(const vector<Expense> &expenses);
void generateReport(const vector<Expense> &expenses, float totalSpent, float spendingLimit);
void saveReportToFile(const map<string, float> &categoryWise, const map<string, float> &dateWise, float totalSpent, float spendingLimit);
void setMonthlySpendingLimit(float &spendingLimit);

int main() {
    vector<Expense> expenses;  // List of all expenses
    float totalSpent = 0.0f;   // Total amount spent
    float spendingLimit = 5000.0f; // Default monthly spending limit
    int choice;

    do {
        cout << "\n--- Expense Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Generate Report\n";
        cout << "4. Set/Update Monthly Spending Limit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addExpense(expenses, totalSpent);
            break;
        case 2:
            viewExpenses(expenses);
            break;
        case 3:
            generateReport(expenses, totalSpent, spendingLimit);
            break;
        case 4:
            setMonthlySpendingLimit(spendingLimit);
            break;
        case 5:
            cout << "Exiting Expense Tracker. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void addExpense(vector<Expense> &expenses, float &totalSpent) {
    Expense newExpense;

    cout << "\nEnter expense details:\n";
    cout << "Category: ";
    cin >> newExpense.category;
    cout << "Description: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newExpense.description);
    cout << "Amount: ";
    cin >> newExpense.amount;
    cout << "Date (DD MM YYYY): ";
    cin >> newExpense.date.day >> newExpense.date.month >> newExpense.date.year;

    expenses.push_back(newExpense);
    totalSpent += newExpense.amount;

    cout << "Expense added successfully!\n";
}

void viewExpenses(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }
    cout << "\n--- All Expenses ---\n";
    for (const auto &expense : expenses) {
        cout << "Category: " << expense.category << "\n";
        cout << "Description: " << expense.description << "\n";
        cout << "Amount: " << fixed << setprecision(2) << expense.amount << "/-\n";
        cout << "Date: " << expense.date.day << "/" << expense.date.month << "/" << expense.date.year << "\n";
        cout << "-------------------------\n";
    }
}

void generateReport(const vector<Expense> &expenses, float totalSpent, float spendingLimit) {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    map<string, float> categoryWise;
    map<string, float> dateWise;  


    for (const auto &expense : expenses) {
        categoryWise[expense.category] += expense.amount;

        string dateStr = to_string(expense.date.day) + "/" +
                         to_string(expense.date.month) + "/" +
                         to_string(expense.date.year);
        dateWise[dateStr] += expense.amount;
    }

    cout << "\n--- Expense Report ---\n";
    cout << "Total Expenses: " << fixed << setprecision(2) << totalSpent << "/-\n";
    cout << "Monthly Spending Limit: " << spendingLimit << "/-\n";
    cout << "Remaining Limit: " << (spendingLimit - totalSpent) << "/-\n\n";

    cout << "Category-Wise Breakdown:\n";
    for (const auto &entry : categoryWise) {
        cout << "- " << entry.first << ": " << fixed << setprecision(2) << entry.second << "/-\n";
    }

    cout << "\nDate-Wise Breakdown:\n";
    for (const auto &entry : dateWise) {
        cout << "- " << entry.first << ": " << fixed << setprecision(2) << entry.second << "/-\n";
    }

    saveReportToFile(categoryWise, dateWise, totalSpent, spendingLimit);
}

void saveReportToFile(const map<string, float> &categoryWise, const map<string, float> &dateWise, float totalSpent, float spendingLimit) {
    ofstream reportFile("Expense_Report.txt");
    if (!reportFile) {
        cout << "Error: Could not create report file.\n";
        return;
    }

    reportFile << "--- Expense Report ---\n";
    reportFile << "Total Expenses: " << fixed << setprecision(2) << totalSpent << "/-\n";
    reportFile << "Monthly Spending Limit: " << spendingLimit << "/-\n";
    reportFile << "Remaining Limit: " << (spendingLimit - totalSpent) << "/-\n\n";

    reportFile << "Category-Wise Breakdown:\n";
    for (const auto &entry : categoryWise) {
        reportFile << "- " << entry.first << ": " << fixed << setprecision(2) << entry.second << "/-\n";
    }

    reportFile << "\nDate-Wise Breakdown:\n";
    for (const auto &entry : dateWise) {
        reportFile << "- " << entry.first << ": " << fixed << setprecision(2) << entry.second << "/-\n";
    }

    reportFile.close();
    cout << "Report saved to 'Expense_Report.txt'.\n";
}

void setMonthlySpendingLimit(float &spendingLimit) {
    cout << "Current Spending Limit: " << spendingLimit << "/-\n";
    cout << "Enter new spending limit: ";
    cin >> spendingLimit;
    cout << "Spending limit updated to: " << spendingLimit << "/-\n";
}
