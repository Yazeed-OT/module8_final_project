/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "Account.h"
#include "Transaction.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>      // For time operations
#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
// Remove <filesystem> since it's causing errors and not used

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// Adds a new customer to the bank
void Bank::addCustomer(int id, const std::string& name) {
    if (name.empty()) { // Check if the name is empty
        std::cerr << "Customer name cannot be empty.\n";
        return;
    }
    if (customers.find(id) != customers.end()) { // Check if the ID already exists
        std::cerr << "Customer with ID " << id << " already exists.\n";
        return;
    }
    // Add the customer to the collection
    customers.emplace(id, Customer(id, name));
    std::cout << "Added customer: " << name << " with ID " << id << "\n";
}

// Removes a customer if they have no accounts with non-zero balances
void Bank::removeCustomer(int id) {
    auto it = customers.find(id);
    if (it == customers.end()) { // Check if the customer exists
        std::cerr << "Customer not found.\n";
        return;
    }
    // Ensure all accounts have a zero balance before removing
    const auto& accounts = it->second.getAccounts();
    for (const auto& account : accounts) {
        if (account->getBalance() != 0) {
            std::cerr << "Cannot remove customer with non-zero account balances.\n";
            return;
        }
    }
    // Remove the customer
    customers.erase(id);
    std::cout << "Removed customer with ID " << id << "\n";
}

// Retrieves a customer by ID
Customer* Bank::getCustomer(int id) {
    auto it = customers.find(id);
    if (it != customers.end()) { // If the customer exists, return it
        return &it->second;
    } else {
        std::cerr << "Customer not found.\n";
        return nullptr;
    }
}

// Displays all customers and their accounts
void Bank::displayAllCustomers() const {
    if (customers.empty()) {
        std::cout << RED "No customers found.\n" RESET;
        return;
    }
    std::cout << BLUE "\n--- Customer Accounts Overview ---\n" RESET;
    int totalCustomers = 0;
    int customersWithAccounts = 0;
    for (const auto& customerPair : customers) {
        const Customer& customer = customerPair.second;
        customer.displayAccounts();
        totalCustomers++;
        if (!customer.getAccounts().empty()) {
            customersWithAccounts++;
        }
    }
    std::cout << "=====================================\n";
    std::cout << "Total Customers: " << totalCustomers << " | Customers with Accounts: " << customersWithAccounts << "\n";
    std::cout << BLUE "--- End of Overview ---\n" RESET;
}

// Applies interest to all savings accounts in the bank
void Bank::applyInterestToAllSavings() {
    for (auto& customerPair : customers) {
        Customer& customer = customerPair.second;
        for (const auto& account : customer.getAccounts()) {
            // Check if the account is a SavingsAccount and apply interest
            if (SavingsAccount* sa = dynamic_cast<SavingsAccount*>(account.get())) {
                sa->applyInterest();
            }
        }
    }
    std::cout << "Interest applied to all savings accounts.\n";
}

// Helper function to normalize account numbers
std::string normalizeAccountNumber(const std::string& acc) {
    std::string result;
    for (char c : acc) {
        if (!isspace(c)) result += std::toupper(c);
    }
    return result;
}

// Transfers funds from one account to another
void Bank::transferFunds(int /*customerId*/, const std::string& fromAcc, const std::string& toAcc, double amount) {
    auto normalizedFrom = normalizeAccountNumber(fromAcc);
    auto normalizedTo = normalizeAccountNumber(toAcc);

    std::shared_ptr<Account> sourceAccount = nullptr;
    std::shared_ptr<Account> destinationAccount = nullptr;

    // Find source account in ALL customers
    for (auto& customerPair : customers) {
        Customer& customer = customerPair.second;
        sourceAccount = customer.getAccount(normalizedFrom);
        if (sourceAccount) break;
    }

    if (!sourceAccount) {
        std::cerr << "Error: Source account not found.\n";
        return;
    }

    // Find destination account in ALL customers
    for (auto& customerPair : customers) {
        Customer& customer = customerPair.second;
        destinationAccount = customer.getAccount(normalizedTo);
        if (destinationAccount) break;
    }

    if (!destinationAccount) {
        std::cerr << "Error: Destination account not found.\n";
        return;
    }

    // Balance check
    if (sourceAccount->getBalance() < amount) {
        std::cerr << "Error: Insufficient funds in source account.\n";
        return;
    }

    // Execute transfer
    *sourceAccount -= amount;
    *destinationAccount += amount;

    std::cout << "Successfully transferred $" << amount
              << " from " << fromAcc << " to " << toAcc << ".\n";
}

// Displays the transaction history for a specific account
void Bank::displayAccountTransactions(int customerId, const std::string& accountNumber) {
    Customer* customer = getCustomer(customerId);
    if (!customer) return;

    for (const auto& account : customer->getAccounts()) { // Use '->' instead of '.'
        if (account->getAccountNumber() == accountNumber) {
            account->displayTransactionHistory();
            return;
        }
    }
    std::cerr << "Account not found.\n";
}

// Loads customer and account data from a file
void Bank::loadData(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: No data file found. Starting fresh.\n";
        return;
    }

    customers.clear();
    std::string line;
    Customer* currentCustomer = nullptr;

    while (std::getline(inFile, line)) {
        if (line.find("Customer ID:") != std::string::npos) {
            int id;
            std::string name;

            size_t idStart = line.find("Customer ID:") + 12;
            size_t nameStart = line.find(", Name:") + 8;

            id = std::stoi(line.substr(idStart, nameStart - idStart - 8));
            name = line.substr(nameStart);

            addCustomer(id, name);
            currentCustomer = getCustomer(id);
        } else if (line.find("Savings Account") != std::string::npos) {
            std::string accountNumber;
            double balance, interestRate;

            // Use a safer approach to extract data
            size_t accNumStart = line.find("Account Number:") + 15;
            size_t balanceStart = line.find("Balance: $") + 10;
            size_t interestStart = line.find("Interest Rate:") + 15;

            accountNumber = line.substr(accNumStart, line.find(",", accNumStart) - accNumStart);
            balance = std::stod(line.substr(balanceStart, line.find(",", balanceStart) - balanceStart));
            interestRate = std::stod(line.substr(interestStart));

            if (currentCustomer) {
                currentCustomer->addAccount(std::make_shared<SavingsAccount>(accountNumber, balance, interestRate));
            }
        } else if (line.find("Checking Account") != std::string::npos) {
            std::string accountNumber;
            double balance, overdraftLimit;

            size_t accNumStart = line.find("Account Number:") + 15;
            size_t balanceStart = line.find("Balance: $") + 10;
            size_t overdraftStart = line.find("Overdraft Limit: $") + 18;

            accountNumber = line.substr(accNumStart, line.find(",", accNumStart) - accNumStart);
            balance = std::stod(line.substr(balanceStart, line.find(",", balanceStart) - balanceStart));
            overdraftLimit = std::stod(line.substr(overdraftStart));

            if (currentCustomer) {
                currentCustomer->addAccount(std::make_shared<CheckingAccount>(accountNumber, balance, overdraftLimit));
            }
        }
    }

    inFile.close();
    std::cout << "Data loaded successfully.\n";
}

// Generates a financial report and writes it to a file
void Bank::generateFinancialReport(const std::string& baseFilename) const {
    // Create reports directory
#ifdef USE_FILESYSTEM
    fs::create_directories("reports");
#else
    struct stat st;
    if (stat("reports", &st) == -1) {
        mkdir("reports", 0775);
    }
#endif

    // Create timestamp
    std::time_t now = std::time(nullptr);
    struct tm localTime;
    localtime_r(&now, &localTime); // Thread-safe version
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &localTime);

    std::string filename = "reports/" + baseFilename + "_" + std::string(buf) + ".txt";

    std::ofstream reportFile(filename, std::ios::out);
    if (!reportFile) {
        std::cerr << "Error: Failed to create report file.\n";
        return;
    }

    double totalFunds = 0.0;
    double totalSavings = 0.0;
    double totalChecking = 0.0;
    // Add report header
    reportFile << "=== Financial Report ===\n";
    reportFile << "Generated on: " << std::ctime(&now);
    reportFile << "Total Customers: " << customers.size() << "\n\n";

    reportFile << std::left << std::setw(20) << "Account Type"
               << std::setw(20) << "Account Number"
               << std::setw(15) << "Balance"
               << std::setw(20) << "Extra Info"
               << "\n";
    reportFile << std::string(75, '-') << "\n";

    for (const auto& customerPair : customers) {
        const Customer& customer = customerPair.second;
        reportFile << "Customer ID: " << customer.getId()
                   << ", Name: " << customer.getName() << "\n";

        for (const auto& account : customer.getAccounts()) {
            totalFunds += account->getBalance();

            if (auto sa = dynamic_cast<SavingsAccount*>(account.get())) {
                reportFile << std::left << std::setw(20) << "Savings"
                           << std::setw(20) << sa->getAccountNumber()
                           << "$" << std::setw(14) << std::fixed << std::setprecision(2) << sa->getBalance()
                           << "Interest: " << sa->getInterestRate() << "%\n";
                totalSavings += sa->getBalance();
            } else if (auto ca = dynamic_cast<CheckingAccount*>(account.get())) {
                reportFile << std::left << std::setw(20) << "Checking"
                           << std::setw(20) << ca->getAccountNumber()
                           << "$" << std::setw(14) << std::fixed << std::setprecision(2) << ca->getBalance()
                           << "Overdraft: $" << ca->getOverdraftLimit() << "\n";
                totalChecking += ca->getBalance();
            }

            // Add transaction history
            reportFile << "  Transaction History:\n";
            for (const auto& t : account->getTransactionHistory()) {
                reportFile << "    - " << std::setw(25) << t.getTimestamp()
                           << std::setw(15) << t.getType()
                           << "$" << std::fixed << std::setprecision(2) << t.getAmount() << "\n";
            }

            reportFile << "---------------------------------------\n";
        }
    }
    reportFile << "\nTotal Funds Across All Accounts: $"
               << std::fixed << std::setprecision(2) << totalFunds << "\n";

    // Add final totals section
    reportFile << "\n===== Totals =====\n";
    reportFile << "Total Savings: $" << std::fixed << std::setprecision(2) << totalSavings << "\n";
    reportFile << "Total Checking: $" << std::fixed << std::setprecision(2) << totalChecking << "\n";
    reportFile << "Grand Total:   $" << std::fixed << std::setprecision(2) << totalFunds << "\n";

    reportFile.close();
    // Print a short message instead of the whole report
    std::cout << "\nReport generated successfully: " << filename << "\n";
    std::cout << "Summary -> Customers: " << customers.size()
              << " | Savings: $" << totalSavings
              << " | Checking: $" << totalChecking
              << " | Grand Total: $" << totalFunds << "\n";

    // Auto-open the report
#ifdef _WIN32
    std::string command = "start " + filename;
#else
    std::string command = "xdg-open " + filename;
#endif
    system(command.c_str());
}

// Saves customer and account data to a file
void Bank::saveData(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::out);
    if (!outFile) {
        std::cerr << "Error: Failed to open file for saving.\n";
        return;
    }

    for (const auto& customerPair : customers) {
        int id = customerPair.first;
        const Customer& customer = customerPair.second;
        outFile << "Customer ID: " << id << ", Name: " << customer.getName() << "\n";

        for (const auto& account : customer.getAccounts()) {
            if (SavingsAccount* sa = dynamic_cast<SavingsAccount*>(account.get())) {
                outFile << "  Savings Account - Account Number: " << sa->getAccountNumber()
                        << ", Balance: $" << std::fixed << std::setprecision(2) << sa->getBalance()
                        << ", Interest Rate: " << sa->getInterestRate() << "%\n";
            } else if (CheckingAccount* ca = dynamic_cast<CheckingAccount*>(account.get())) {
                outFile << "  Checking Account - Account Number: " << ca->getAccountNumber()
                        << ", Balance: $" << std::fixed << std::setprecision(2) << ca->getBalance()
                        << ", Overdraft Limit: $" << ca->getOverdraftLimit() << "\n";
            }
        }

        outFile << "---------------------------------------\n";
    }

    outFile.close();
    std::cout << "Data saved successfully.\n";
}
