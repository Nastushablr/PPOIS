#include "documents/FinancialReport.h"
#include <sstream>

using namespace std;

FinancialReport::FinancialReport()
    : Document(),
    periodLabel(""),
    invoices(),
    payments(),
    totalInvoiced(0.0),
    totalPaid(0.0),
    totalOutstanding(0.0) {
}

FinancialReport::FinancialReport(int id,
    const Date& created,
    Employee* author,
    const string& periodLabel)
    : Document(id, created, author),
    periodLabel(periodLabel),
    invoices(),
    payments(),
    totalInvoiced(0.0),
    totalPaid(0.0),
    totalOutstanding(0.0) {
}

const string& FinancialReport::getPeriodLabel() const { return periodLabel; }
const vector<Invoice*>& FinancialReport::getInvoices() const { return invoices; }
const vector<Payment*>& FinancialReport::getPayments() const { return payments; }
double FinancialReport::getTotalInvoiced() const { return totalInvoiced; }
double FinancialReport::getTotalPaid() const { return totalPaid; }
double FinancialReport::getTotalOutstanding() const { return totalOutstanding; }

void FinancialReport::addInvoice(Invoice* invoice) {
    if (invoice) invoices.push_back(invoice);
}

void FinancialReport::addPayment(Payment* payment) {
    if (payment) payments.push_back(payment);
}

void FinancialReport::clearData() {
    invoices.clear();
    payments.clear();
    totalInvoiced = 0.0;
    totalPaid = 0.0;
    totalOutstanding = 0.0;
}

void FinancialReport::recalculateTotals() {
    totalInvoiced = 0.0;
    totalPaid = 0.0;

    for (auto* inv : invoices) {
        if (inv) totalInvoiced += inv->getTotalWithTax();
    }

    for (auto* pay : payments) {
        if (pay && !pay->isRefunded()) {
            totalPaid += pay->getAmount();
        }
    }

    totalOutstanding = totalInvoiced - totalPaid;
    if (totalOutstanding < 0.0) totalOutstanding = 0.0;
}

double FinancialReport::getPaidPercent() const {
    if (totalInvoiced <= 0.0) return 0.0;
    return (totalPaid / totalInvoiced) * 100.0;
}

string FinancialReport::generateSummary() const {
    stringstream ss;
    ss << "FinancialReport " << periodLabel
        << " invoiced=" << totalInvoiced
        << " paid=" << totalPaid
        << " outstanding=" << totalOutstanding;
    return ss.str();
}
