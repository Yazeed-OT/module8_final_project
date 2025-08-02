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

#include "Account.h"
#include <iostream>
#include <iomanip> // Required for std::left, std::right, std::setw, std::fixed, std::setprecision
#include <cmath>   // Required for std::fixed and std::setprecision

// Constructor to initialize account number and balance
Account::Account(const std::string& accountNumber, double balance)
    : accountNumber(accountNumber), balance(balance) {}

// Destructor for the Account class (not doing anything specific here)
Account::~Account() {}

// Adds money to the account and records the transaction
void Account::deposit(double amount) {
    balance += amount; // Increase balance by the deposit amount
    recordTransaction("Deposit", amount); // Record this transaction in the history
    std::cout << "Deposited $" << amount << ". New balance: $" << balance << "\n";
}

// Removes money from the account if enough balance is available
void Account::withdraw(double amount) {
    if (amount > balance) {
        // If the withdrawal amount is greater than the balance, show an error
        std::cerr << "Insufficient funds. Current balance: $" << balance << "\n";
    } else {
        balance -= amount; // Deduct the amount from the balance
        recordTransaction("Withdrawal", amount); // Record this transaction in the history
        std::cout << "Withdrew $" << amount << ". New balance: $" << balance << "\n";
    }
}

// Displays basic account details like account number and balance
void Account::displayDetails() const {
    std::cout << "  Account Number : " << std::left << std::setw(15) << accountNumber << "\n"
              << "  Balance        : " << std::right << GREEN "$" << std::setw(10) << std::fixed << std::setprecision(2) << balance << RESET "\n";
}

// Base account does not apply interest, but derived classes can override this
void Account::applyInterest() {
    // This is intentionally left empty since base accounts don't earn interest
}

// Records a transaction with its type (e.g., "Deposit" or "Withdrawal") and amount
void Account::recordTransaction(const std::string& type, double amount) {
    transactionHistory.emplace_back(type, amount); // Add the transaction to the history
}

// Displays all transactions for this account
void Account::displayTransactionHistory() const {
    std::cout << "Transaction History for Account " << accountNumber << ":\n";
    if (transactionHistory.empty()) {
        // If no transactions exist, show a message
        std::cout << "No transactions found.\n";
    } else {
        // Loop through the transaction history and display each transaction
        for (const auto& txn : transactionHistory) {
            txn.displayTransaction();
        }
    }
}

// Getter for the account number
std::string Account::getAccountNumber() const {
    return accountNumber;
}

// Getter for the balance
double Account::getBalance() const {
    return balance;
}

// Overloaded += operator to deposit money into the account
Account& Account::operator+=(double amount) {
    deposit(amount); // Use the deposit method to add money
    return *this; // Return the current object
}

// Overloaded -= operator to withdraw money from the account
Account& Account::operator-=(double amount) {
    withdraw(amount); // Use the withdraw method to remove money
    return *this; // Return the current object
}

// Overloaded == operator to compare two accounts by their account number
bool Account::operator==(const Account& other) const {
    return this->accountNumber == other.accountNumber; // Compare account numbers
}
