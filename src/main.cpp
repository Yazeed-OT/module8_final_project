/*
 * Final Project
 * Author: Yazeed Alotaibi
 * Course: CSCI 201 – Computer Science II
 * Date: 07/14/2025
 */

#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <limits>
#include <filesystem>
#include <fstream>

// Function to display the main menu for the banking system
void displayMenu() {
    std::cout << "\n--- Banking System Menu ---\n";
    std::cout << "1. Add Customer\n";               // Add a new customer
    std::cout << "2. Add Account\n";                // Add a new account for an existing customer
    std::cout << "3. Display All Customers\n";      // Show details of all customers and their accounts
    std::cout << "4. Apply Interest to Savings\n";  // Apply interest to all savings accounts
    std::cout << "5. Transfer Funds\n";             // Transfer funds between accounts
    std::cout << "6. Generate Financial Report\n";  // Create a financial report with account details
    std::cout << "7. Exit\n";                       // Exit the program
}

int main() {
    Bank bank; // Create a Bank object to manage customers and accounts
    const std::string filename = "bank_data.txt"; // File to save and load data
    const std::string defaultFile = "default_data.txt";

    // If no bank_data.txt exists, copy from default_data.txt
    if (!std::filesystem::exists(filename)) {
        std::ifstream src(defaultFile, std::ios::binary);
        std::ofstream dst(filename, std::ios::binary);
        if (src && dst) {
            dst << src.rdbuf();  // copy contents
            std::cout << "Loaded default demo data from " << defaultFile << "\n";
        } else {
            std::cerr << "Error: Could not load default data file.\n";
        }
    }

    // Load previously saved data when the program starts
    bank.loadData(filename);

    int choice; // Variable to store the user's menu choice
    while (true) {
        displayMenu(); // Show the menu
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input. Please enter a valid numeric choice.\n";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            continue; // Redisplay the menu
        }

        // Exit the program if the user selects 7
        if (choice == 7) break;

        // Variables to store user inputs
        int id;
        std::string name, accountNumber, fromAcc, toAcc;
        double balance, interestRate, overdraftLimit, amount;

        // Handle the user's choice
        switch (choice) {
        case 1: {
            // Add a new customer
            std::cout << "Enter Customer ID: ";
            while (!(std::cin >> id)) {
                std::cerr << "Invalid input. Please enter a valid numeric ID.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Customer ID: ";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any leftover input
            std::cout << "Enter Customer Name: ";
            std::getline(std::cin, name); // Get the customer's name (allowing spaces)

            std::cout << "DEBUG: Adding Customer with ID: " << id << " and Name: " << name << "\n"; // Debug info
            bank.addCustomer(id, name); // Add the customer to the bank
            break;
        }

        case 2:
            // Add a new account for an existing customer
            std::cout << "Enter Customer ID: ";
            while (!(std::cin >> id)) {
                std::cerr << "Invalid input. Please enter a valid numeric ID.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Customer ID: ";
            }
            if (Customer* customer = bank.getCustomer(id)) { // Check if the customer exists
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Initial Balance: ";
                while (!(std::cin >> balance) || balance < 0) {
                    std::cerr << "Invalid input. Balance cannot be negative.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter Initial Balance: ";
                }

                std::cout << "1: Savings, 2: Checking: ";
                int type;
                while (!(std::cin >> type) || (type != 1 && type != 2)) {
                    std::cerr << "Invalid input. Please enter 1 for Savings or 2 for Checking.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "1: Savings, 2: Checking: ";
                }

                if (type == 1) {
                    std::cout << "Enter Interest Rate: ";
                    while (!(std::cin >> interestRate) || interestRate < 0) {
                        std::cerr << "Invalid input. Interest rate cannot be negative.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Enter Interest Rate: ";
                    }
                    customer->addAccount(std::make_shared<SavingsAccount>(accountNumber, balance, interestRate));
                } else if (type == 2) {
                    std::cout << "Enter Overdraft Limit: ";
                    while (!(std::cin >> overdraftLimit) || overdraftLimit < 0) {
                        std::cerr << "Invalid input. Overdraft limit cannot be negative.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Enter Overdraft Limit: ";
                    }
                    customer->addAccount(std::make_shared<CheckingAccount>(accountNumber, balance, overdraftLimit));
                }
            }
            break;

        case 3:
            // Display all customers and their accounts
            bank.displayAllCustomers();
            break;

        case 4:
            // Apply interest to all savings accounts
            bank.applyInterestToAllSavings();
            break;

        case 5:
            // Transfer funds between accounts
            std::cout << "Enter Customer ID: ";
            while (!(std::cin >> id)) {
                std::cerr << "Invalid input. Please enter a valid numeric ID.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Customer ID: ";
            }
            std::cout << "From Account: ";
            std::cin >> fromAcc;
            std::cout << "To Account: ";
            std::cin >> toAcc;
            std::cout << "Enter Amount: ";
            while (!(std::cin >> amount) || amount < 0) {
                std::cerr << "Invalid input. Amount cannot be negative.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Amount: ";
            }
            bank.transferFunds(id, fromAcc, toAcc, amount);
            break;

        case 6: {
            // Generate a financial report and save it to a file
            std::string reportFile = "financial_report.txt";
            bank.generateFinancialReport(reportFile);
            break;
        }

        default:
            // Handle invalid menu choices
            std::cerr << "Invalid choice.\n";
        }
    }

    // Save all data before exiting the program
    bank.saveData(filename);

    return 0; // Program ends
}
