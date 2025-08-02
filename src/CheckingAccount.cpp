/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

#include "CheckingAccount.h"
#include <iostream>
#include <iomanip> // Required for std::left, std::right, std::setw, std::fixed, std::setprecision

// Constructor for CheckingAccount class
// Initializes the account number, balance, and overdraft limit
CheckingAccount::CheckingAccount(const std::string& accountNumber, double balance, double overdraftLimit)
    : Account(accountNumber, balance), overdraftLimit(overdraftLimit) {}

// Method to withdraw money from the checking account
// Checks if the withdrawal amount exceeds the balance and overdraft limit
void CheckingAccount::withdraw(double amount) {
    if (amount > balance + overdraftLimit) {
        // If the amount is too high, print an error message
        std::cerr << "Overdraft limit exceeded. Current balance: $" << balance << "\n";
    } else {
        // Deduct the amount from the balance and record the transaction
        balance -= amount;
        recordTransaction("Withdrawal", amount);
        std::cout << "Withdrew $" << amount << ". New balance: $" << balance << "\n";
    }
}

// Method to display the details of the checking account
// Shows account number, balance, and overdraft limit
void CheckingAccount::displayDetails() const {
    Account::displayDetails();
    std::cout << "  Overdraft Limit: " << std::right << GREEN "$" << std::setw(10) << overdraftLimit << RESET "\n";
}
