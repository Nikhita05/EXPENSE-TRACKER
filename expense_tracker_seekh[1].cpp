#include <stdio.h>
#include <stdlib.h>

// Structure to represent a date
struct Date {
    int day;
    int month;
    int year;
};

// Structure to represent an expense
struct Expense {
    char description[100];
    float amount;
    struct Date date;
};

// Function to add an expense
void addExpense(struct Expense expenses[], int *count, float spendingLimit, float *totalSpent) {
    if (*count < 100) {
        printf("Enter expense description: ");
        if (scanf("%99s", expenses[*count].description) != 1) {
            printf("Error reading description.\n");
            return;
        }

        printf("Enter expense amount: ");
        if (scanf("%f", &expenses[*count].amount) != 1) {
            printf("Error reading amount.\n");
            return;
        }

        printf("Enter expense date (dd mm yy): ");
        if (scanf("%d %d %d", &expenses[*count].date.day, &expenses[*count].date.month, &expenses[*count].date.year) != 3) {
            printf("Error reading date.\n");
            return;
        }

        // Check if a monthly spending limit is set
        if (spendingLimit > 0) {
            // Check if the expense exceeds the remaining spending limit
            if (expenses[*count].amount > spendingLimit - *totalSpent) {
                printf("Error: Expense exceeds the remaining spending limit.\n");
                printf("Remaining Spending Limit: %.2f/-\n", spendingLimit - *totalSpent);
                return;
            } else {
                *totalSpent += expenses[*count].amount;
                printf("Expense added successfully!\n");
                printf("Remaining Spending Limit: %.2f/-\n", spendingLimit - *totalSpent);
            }
        } else {
            *totalSpent += expenses[*count].amount;
            printf("Expense added successfully!\n");
        }

        (*count)++;
    } else {
        printf("Error: Maximum number of expenses reached.\n");
    }
}

// Function to view total expenses
void viewTotalExpenses(struct Expense expenses[], int count) {
    float total = 0;

    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }

    printf("Total Expenses: %.2f/-\n", total);
}

// Function to view individual expenses
void viewIndividualExpenses(struct Expense expenses[], int count) {
    if (count == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("Individual Expenses:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Description: %s, Amount: %.2f/-, Date: %02d/%02d/%02d\n", i + 1, expenses[i].description, expenses[i].amount,
               expenses[i].date.day, expenses[i].date.month, expenses[i].date.year);
    }
}

// Function to set monthly spending limit
float setMonthlyLimit(float *spendingLimit) {
    printf("Enter your monthly spending limit: ");
    if (scanf("%f", spendingLimit) != 1) {
        printf("Error reading spending limit.\n");
        return 0;
    }
    printf("Monthly spending limit set to %.2f/-\n", *spendingLimit);
    return *spendingLimit;
}

// Function to display remaining spending limit
void displayRemainingLimit(float spendingLimit, float totalSpent) {
    float remaining = spendingLimit - totalSpent;
    printf("Remaining Spending Limit: %.2f/-\n", remaining);
}

int main() {
    struct Expense expenses[100];  // Assuming a maximum of 100 expenses
    int count = 0;
    int choice;
    float spendingLimit = 0;
    float totalSpent = 0;

    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Total Expenses\n");
        printf("3. View Individual Expenses\n");
        printf("4. Set Monthly Spending Limit\n");
        printf("5. Display Remaining Spending Limit\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error reading choice.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addExpense(expenses, &count, spendingLimit, &totalSpent);
                break;
            case 2:
                viewTotalExpenses(expenses, count);
                break;
            case 3:
                viewIndividualExpenses(expenses, count);
                break;
            case 4:
                spendingLimit = setMonthlyLimit(&spendingLimit);
                break;
            case 5:
                displayRemainingLimit(spendingLimit, totalSpent);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
