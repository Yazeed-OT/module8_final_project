/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Transaction.h"
#include <string>
#include <vector>

// The Account class represents a bank account with basic functionalities 
// like deposits, withdrawals, and maintaining transaction history.
class Account {
protected:
    // Unique account number for identifying the account
    std::string accountNumber;

    // Current balance of the account
    double balance;

    // History of all transactions made with this account
    std::vector<Transaction> transactionHistory;

public:
    // Constructor to initialize an account with an account number and an optional initial balance
    Account(const std::string& accountNumber, double balance = 0.0);

    // Virtual destructor to allow cleanup in derived classes
    virtual ~Account();

    // Method to deposit money into the account
    virtual void deposit(double amount);

    // Method to withdraw money from the account
    virtual void withdraw(double amount);

    // Method to display account details like account number and balance
    virtual void displayDetails() const;

    // Virtual method for applying interest (overridden in derived classes)
    virtual void applyInterest();

    // Records a transaction with the given type (e.g., deposit, withdrawal) and amount
    void recordTransaction(const std::string& type, double amount);

    // Displays the transaction history for the account
    void displayTransactionHistory() const;

    // Returns the transaction history for the account
    const std::vector<Transaction>& getTransactionHistory() const { return transactionHistory; }

    // Getter for the account number
    std::string getAccountNumber() const;

    // Getter for the current account balance
    double getBalance() const;

    // Overloaded operator to add an amount to the account balance
    Account& operator+=(double amount);

    // Overloaded operator to subtract an amount from the account balance
    Account& operator-=(double amount);

    // Overloaded equality operator to compare accounts by their account number
    bool operator==(const Account& other) const;
};

#endif
