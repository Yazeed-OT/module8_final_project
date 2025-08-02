/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// This class represents a financial transaction in the banking system
class Transaction {
private:
    std::string transactionId; // Unique ID for the transaction
    std::string type;          // Type of transaction (e.g., Deposit, Withdrawal)
    double amount;             // Amount of money involved in the transaction
    std::string timestamp;     // When the transaction occurred

    // Static helper method to generate unique transaction IDs
    static std::string generateTransactionId();

public:
    // Constructor to initialize a transaction with its type and amount
    Transaction(const std::string& type, double amount);

    // Displays the details of the transaction (ID, type, amount, timestamp)
    void displayTransaction() const;

    // Getter for the transaction timestamp
    std::string getTimestamp() const { return timestamp; }

    // Getter for the transaction type
    std::string getType() const { return type; }

    // Getter for the transaction amount
    double getAmount() const { return amount; }
};

#endif
