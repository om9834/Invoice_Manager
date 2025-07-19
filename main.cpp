#include <iostream>
#include "invoice.h"
using namespace std;

int main() {
    int choice;
    std::string client;

    do {
        cout << "\n========= Invoice Tracker =========\n";
        cout << "1. Add Invoice\n";
        cout << "2. View All Invoices\n";
        cout << "3. Search Invoice by Client Name\n";
        cout << "4. Delete Paid Invoices\n"; 
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        cin >> choice;

        switch(choice) {
            case 1:
                addInvoice();
                break;
            case 2:
                viewInvoices();
                break;
            case 3:
                cout << "Enter client name to search: ";
                cin >> client;
                searchInvoice(client);
                break;
            case 4:
                deletePaidInvoices();
                break;
            case 0:
                cout << " Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

 /*g++ main.cpp invoice.cpp -o invoice.exe
 ./invoice.exe*/