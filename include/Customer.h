/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Account.h"
#include <memory>
#include <vector>

class Customer {
private:
    int id;  // Unique ID for the customer
    std::string name;  // Name of the customer
    std::vector<std::shared_ptr<Account>> accounts;  // List of accounts owned by the customer

public:
    // Constructor: Initializes a customer with an ID and name
    Customer(int id, const std::string& name);

    // Adds a new account to the customer's list of accounts
    // The account is passed as a shared pointer to allow shared ownership
    void addAccount(const std::shared_ptr<Account>& account);

    // Removes an account by its account number
    // Only removes the account if its balance is zero
    void removeAccount(const std::string& accountNumber);

    // Displays all accounts owned by the customer
    // Shows account details like balance, account type, etc.
    void displayAccounts() const;

    // Returns a constant reference to the vector of accounts
    // This allows access to the list of accounts without modification
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;

    // Searches for an account by its account number
    // If found, returns a shared pointer to the account; otherwise, returns nullptr
    std::shared_ptr<Account> getAccount(const std::string& accountNumber) const;

    // Getter for the customer's ID
    int getId() const;

    // Getter for the customer's name
    std::string getName() const;
};

#endif
