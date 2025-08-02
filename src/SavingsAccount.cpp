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

#include "SavingsAccount.h"
#include <iostream>
#include <iomanip> // Required for std::left, std::right, std::setw, std::fixed, std::setprecision

// Constructor for the SavingsAccount class
// Initializes the account number, balance, and interest rate
SavingsAccount::SavingsAccount(const std::string& accountNumber, double balance, double interestRate)
    : Account(accountNumber, balance), interestRate(interestRate) {}

// Method to apply interest to the savings account balance
// Calculates the interest based on the balance and interest rate
// Adds the interest to the balance and records it as a transaction
void SavingsAccount::applyInterest() {
    double interest = balance * (interestRate / 100); // Calculate interest
    balance += interest; // Add interest to balance
    recordTransaction("Interest Applied ", interest); // Log the transaction
    std::cout << "Applied interest: $" << std::fixed << std::setprecision(2) 
              << interest << ". New balance: $" << balance << "\n"; // Show the updated balance
}

// Method to display details of the savings account
// Includes account number, balance, and the interest rate
void SavingsAccount::displayDetails() const {
    Account::displayDetails();
    std::cout << "  Interest Rate  : " << std::right << YELLOW << std::setw(6) << interestRate << "%" RESET "\n";
}
