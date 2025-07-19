#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "invoice.h"

void addInvoice() {
    Invoice inv;
    std::cout << "Enter Invoice ID: ";
    std::cin >> inv.id;
    std::cin.ignore();
    std::cout << "Enter Client Name: ";
    std::getline(std::cin, inv.clientName);
    std::cout << "Enter Amount: ";
    std::cin >> inv.amount;
    std::cout << "Enter Due Date (DD/MM/YYYY): ";
    std::cin >> inv.dueDate;
    inv.isPaid = false;

    std::ofstream file("invoices.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout << " Error: Could not open invoices.txt to write!\n";
        return;
    }

    file << inv.id << "," << inv.clientName << "," << inv.amount << "," << inv.dueDate << "," << inv.isPaid << "\n";
    file.close();

    std::cout << " Invoice added successfully!\n";
}

void viewInvoices() {
    std::ifstream file("invoices.txt");
    std::string line;
    std::cout << "\n All Invoices:\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "ID\tClient\t\tAmount\tDue Date\tPaid\n";
    std::cout << "--------------------------------------------------\n";

    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        Invoice inv;
        iss >> inv.id >> inv.clientName >> inv.amount >> inv.dueDate >> inv.isPaid;
        std::cout << inv.id << "\t" << inv.clientName << "\t\t" << inv.amount << "\t" << inv.dueDate << "\t" << (inv.isPaid ? "Yes" : "No") << "\n";
    }

    file.close();
}

void searchInvoice(const std::string& name) {
    std::ifstream file("invoices.txt");
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        Invoice inv;
        iss >> inv.id >> inv.clientName >> inv.amount >> inv.dueDate >> inv.isPaid;

        if (inv.clientName == name) {
            std::cout << "\n Invoice Found:\n";
            std::cout << "ID: " << inv.id << "\nClient: " << inv.clientName << "\nAmount: ₹" << inv.amount
                      << "\nDue: " << inv.dueDate << "\nPaid: " << (inv.isPaid ? "Yes" : "No") << "\n";
            found = true;
            break;
        }
    }

    if (!found) std::cout << " No invoice found for client: " << name << "\n";
    file.close();
}

void deletePaidInvoices() {
    std::ifstream file("invoices.txt");
    std::ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        std::cout << " Error opening file.\n";
        return;
    }

    std::string line;
    bool deleted = false;

    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        Invoice inv;
        iss >> inv.id >> inv.clientName >> inv.amount >> inv.dueDate >> inv.isPaid;

        if (!inv.isPaid) {
            temp << inv.id << "," << inv.clientName << "," << inv.amount << "," << inv.dueDate << "," << inv.isPaid << "\n";
        } else {
            deleted = true;
        }
    }

    file.close();
    temp.close();

    std::remove("invoices.txt");
    std::rename("temp.txt", "invoices.txt");

    if (deleted)
        std::cout << "Paid invoices deleted successfully.\n";
    else
        std::cout << "No paid invoices found to delete.\n";
}
