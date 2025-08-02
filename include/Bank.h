/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef BANK_H
#define BANK_H

#include "Customer.h"
#include <unordered_map>
#include <string>

class Bank {
private:
    // Stores all customers in the bank using their ID as the key
    std::unordered_map<int, Customer> customers;

public:
    // Adds a new customer to the bank
    // Params:
    // - id: The unique ID of the customer
    // - name: The customer's name
    void addCustomer(int id, const std::string& name);

    // Removes a customer from the bank if they have no active accounts or balances
    // Params:
    // - id: The unique ID of the customer to be removed
    void removeCustomer(int id);

    // Finds and returns a customer by their ID
    // Params:
    // - id: The unique ID of the customer
    // Returns: Pointer to the customer object, or nullptr if not found
    Customer* getCustomer(int id);

    // Displays details of all customers in the bank
    void displayAllCustomers() const;

    // Applies interest to all savings accounts for all customers
    void applyInterestToAllSavings();

    // Transfers funds from one account to another
    // Params:
    // - customerId: The ID of the customer making the transfer
    // - fromAcc: The account number of the source account
    // - toAcc: The account number of the destination account
    // - amount: The amount to transfer
    void transferFunds(int customerId, const std::string& fromAcc, const std::string& toAcc, double amount);

    // Displays all transactions for a specific account of a customer
    // Params:
    // - customerId: The ID of the customer
    // - accountNumber: The account number whose transactions are to be displayed
    void displayAccountTransactions(int customerId, const std::string& accountNumber);

    // Saves all customer and account data to a file
    // Params:
    // - filename: The name of the file where data will be saved
    void saveData(const std::string& filename);

    // Loads all customer and account data from a file
    // Params:
    // - filename: The name of the file to load data from
    void loadData(const std::string& filename);

    // Generates a financial report summarizing all customer and account data
    // Params:
    // - filename: The name of the file where the report will be saved
    void generateFinancialReport(const std::string& filename) const;
};

#endif
