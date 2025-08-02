/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#include "Transaction.h"
#include <iostream>
#include <ctime>

// Generates a unique transaction ID for each transaction.
// Uses a static counter that increments with every new transaction.
std::string Transaction::generateTransactionId() {
    static int counter = 1; // Counter starts at 1 and persists across calls.
    return "TXN" + std::to_string(counter++); // Create an ID like "TXN1", "TXN2", etc.
}

// Constructor for the Transaction class.
// Initializes the transaction with a type (e.g., Deposit, Withdrawal),
// an amount, a unique transaction ID, and a timestamp.
Transaction::Transaction(const std::string& type, double amount)
    : transactionId(generateTransactionId()), type(type), amount(amount) {
    time_t now = time(0);           // Get the current time.
    timestamp = ctime(&now);        // Convert time to a readable string.
    timestamp.pop_back();           // Remove the trailing newline character.
}

// Displays the details of a transaction in a user-friendly format.
// Prints the transaction ID, type, amount, and timestamp.
void Transaction::displayTransaction() const {
    std::cout << "Transaction ID: " << transactionId << "\n"  // Print transaction ID.
              << "Type: " << type << "\n"                    // Print transaction type.
              << "Amount: $" << amount << "\n"               // Print transaction amount.
              << "Timestamp: " << timestamp << "\n\n";       // Print when the transaction happened.
}
