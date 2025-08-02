/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

// This class represents a checking account, which inherits from the base Account class.
// It adds the feature of an overdraft limit, allowing withdrawals beyond the account balance up to a certain amount.
class CheckingAccount : public Account {
private:
    double overdraftLimit; // The maximum amount the account can go negative.

public:
    // Constructor: Creates a CheckingAccount object with a specific account number, balance, and overdraft limit.
    CheckingAccount(const std::string& accountNumber, double balance, double overdraftLimit);

    // Withdraw function: Overrides the base class function to allow overdraft within the set limit.
    void withdraw(double amount) override;

    // Display function: Overrides the base class function to show account details including overdraft limit.
    void displayDetails() const override;

    // Getter for overdraftLimit: Returns the overdraft limit of the account.
    double getOverdraftLimit() const { return overdraftLimit; }
};

#endif
