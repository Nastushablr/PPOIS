#include "documents/Invoice.h"
#include <sstream>

using namespace std;

Invoice::Invoice()
    : Document(),
    client(nullptr),
    amount(0.0),
    taxRate(0.0),
    dueDate(),
    paymentStatus("unpaid"),
    items() {
}

Invoice::Invoice(int id,
    const Date& created,
    Employee* author,
    Client* client,
    double amount,
    double taxRate,
    const Date& dueDate)
    : Document(id, created, author),
    client(client),
    amount(amount),
    taxRate(taxRate),
    dueDate(dueDate),
    paymentStatus("unpaid"),
    items() {
}

Client* Invoice::getClient() const { return client; }
double Invoice::getAmount() const { return amount; }
double Invoice::getTaxRate() const { return taxRate; }
Date Invoice::getDueDate() const { return dueDate; }
const string& Invoice::getPaymentStatus() const { return paymentStatus; }
const vector<string>& Invoice::getItems() const { return items; }

void Invoice::setAmount(double value) { amount = value; }
void Invoice::setTaxRate(double value) { taxRate = value; }
void Invoice::setDueDate(const Date& value) { dueDate = value; }

void Invoice::addItem(const string& line) {
    items.push_back(line);
}

double Invoice::getTotalWithTax() const {
    return amount + amount * taxRate;
}

void Invoice::markPaid() {
    paymentStatus = "paid";
}

bool Invoice::isOverdue(const Date& today) const {
    return paymentStatus != "paid" && (dueDate < today);
}

string Invoice::generateSummary() const {
    stringstream ss;
    ss << "Invoice #" << id << " total " << getTotalWithTax();
    return ss.str();
}
