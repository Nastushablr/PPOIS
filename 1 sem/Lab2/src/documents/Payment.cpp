#include "documents/Payment.h"
#include <sstream>

using namespace std;

Payment::Payment()
    : Document(),
    invoice(nullptr),
    amount(0.0),
    paymentDate(),
    method(""),
    transactionId(""),
    refunded(false) {
}

Payment::Payment(int id,
    const Date& created,
    Employee* author,
    Invoice* invoice,
    double amount,
    const Date& paymentDate,
    const string& method)
    : Document(id, created, author),
    invoice(invoice),
    amount(amount),
    paymentDate(paymentDate),
    method(method),
    transactionId(""),
    refunded(false) {
}

Invoice* Payment::getInvoice() const { return invoice; }
double Payment::getAmount() const { return amount; }
const Date& Payment::getPaymentDate() const { return paymentDate; }
const string& Payment::getMethod() const { return method; }
const string& Payment::getTransactionId() const { return transactionId; }
bool Payment::isRefunded() const { return refunded; }

void Payment::setPaymentDate(const Date& value) { paymentDate = value; }
void Payment::setMethod(const string& value) { method = value; }
void Payment::setTransactionId(const string& value) { transactionId = value; }

void Payment::markProcessed() {
    status = "processed";
}

void Payment::markFailed() {
    status = "failed";
}

void Payment::markRefunded() {
    status = "refunded";
    refunded = true;
}

string Payment::generateSummary() const {
    stringstream ss;
    ss << "Payment #" << id << " amount " << amount
        << " status " << status;
    return ss.str();
}
