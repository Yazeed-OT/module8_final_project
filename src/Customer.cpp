/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "Customer.h"
#include <iostream>
#include <algorithm>  // Required for std::remove_if
#include <iomanip>    // Required for std::fixed and std::setprecision
#include <sstream>    // Required for std::ostringstream
#include <cctype>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// Normalize helper
std::string normalize(const std::string& acc) {
    std::string result;
    for (char c : acc) {
        if (!isspace(c)) result += std::toupper(c);
    }
    return result;
}

// Constructor: Initializes the Customer with an ID and a name
Customer::Customer(int id, const std::string& name) : id(id), name(name) {}

// Adds a new account to the customer's list of accounts
void Customer::addAccount(const std::shared_ptr<Account>& account) {
    // Make sure the account number is not empty
    if (account->getAccountNumber().empty()) {
        std::cerr << "Error: Account number cannot be empty.\n";
        return;
    }

    // Check if an account with the same account number already exists for this customer
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [&](const std::shared_ptr<Account>& acc) {
                               return acc->getAccountNumber() == account->getAccountNumber();
                           });
    if (it != accounts.end()) {
        std::cerr << "Error: Account number already exists for this customer.\n";
        return;
    }

    // Add the new account to the list
    accounts.push_back(account);
    std::cout << "Added account " << account->getAccountNumber() << " for customer " << name << "\n";
}

// Displays all the accounts associated with the customer
void Customer::displayAccounts() const {
    std::cout << BLUE "(ID: " << id << ") " << name << RESET << "\n";
    std::cout << "Account Number   Balance        Overdraft Limit   Interest Rate\n";
    std::cout << "-----------------------------------------------------------------\n";

    for (const auto& account : accounts) {
        std::cout << std::left << std::setw(15) << account->getAccountNumber()
                  << "$" << std::setw(12) << std::fixed << std::setprecision(2) << account->getBalance();

        // Print overdraft for checking
        if (auto ca = dynamic_cast<CheckingAccount*>(account.get())) {
            std::cout << "$" << std::setw(15) << ca->getOverdraftLimit()
                      << std::setw(15) << "-";
        }
        // Print interest for savings
        else if (auto sa = dynamic_cast<SavingsAccount*>(account.get())) {
            std::cout << std::setw(16) << "-" 
                      << std::setw(10) << std::fixed << std::setprecision(2)
                      << sa->getInterestRate() << "%";
        }

        std::cout << "\n";
    }
    std::cout << "=====================================\n";
}

// Finds and returns a specific account based on the account number
std::shared_ptr<Account> Customer::getAccount(const std::string& accountNumber) const {
    std::string normalizedInput = normalize(accountNumber);
    for (const auto& account : accounts) {
        if (normalize(account->getAccountNumber()) == normalizedInput) {
            return account;
        }
    }
    return nullptr;
}

// Removes an account from the customer's list
void Customer::removeAccount(const std::string& accountNumber) {
    // Search for the account by its number
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [&](const std::shared_ptr<Account>& acc) {
                               return acc->getAccountNumber() == accountNumber;
                           });

    if (it != accounts.end()) {
        // Check if the account balance is zero before removing
        if ((*it)->getBalance() == 0) {
            accounts.erase(it);  // Remove the account from the list
            std::cout << "Removed account " << accountNumber << " for customer " << name << "\n";
        } else {
            std::cerr << "Error: Cannot remove account with non-zero balance.\n";  // Prevent removing if the balance isn't zero
        }
    } else {
        std::cerr << "Error: Account with number " << accountNumber << " not found.\n";  // Account doesn't exist
    }
}

// Returns a reference to the list of accounts associated with this customer
const std::vector<std::shared_ptr<Account>>& Customer::getAccounts() const {
    return accounts;
}

// Getter for the customer ID
int Customer::getId() const { return id; }

// Getter for the customer name
std::string Customer::getName() const { return name; }
