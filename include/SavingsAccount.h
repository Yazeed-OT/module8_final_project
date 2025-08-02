/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

// This class represents a Savings Account and inherits from the base Account class.
class SavingsAccount : public Account {
private:
    double interestRate; // The interest rate for this savings account, stored as a percentage.

public:
    // Constructor for creating a SavingsAccount object.
    // Takes an account number, initial balance, and interest rate as parameters.
    SavingsAccount(const std::string& accountNumber, double balance, double interestRate);

    // This method applies interest to the account balance based on the interest rate.
    // Overrides the applyInterest() method from the Account class.
    void applyInterest() override;

    // Displays detailed info about the SavingsAccount, like the balance and interest rate.
    // Overrides the displayDetails() method from the Account class.
    void displayDetails() const override;

    // A getter method to retrieve the interest rate for this account.
    // Returns the interest rate as a double.
    double getInterestRate() const { return interestRate; }
};

#endif
