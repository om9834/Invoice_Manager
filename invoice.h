#ifndef INVOICE_H
#define INVOICE_H



#include <string>

struct Invoice {
    int id;
    std::string clientName;
    float amount;
    std::string dueDate;
    bool isPaid;
};

void addInvoice();
void viewInvoices();
void searchInvoice(const std::string& name);
void deletePaidInvoices();

#endif
