#include "documents/Contract.h"
#include <sstream>

using namespace std;

Contract::Contract()
    : Document(),
    client(nullptr),
    project(nullptr),
    startDate(),
    endDate(),
    amount(0.0),
    termsText("") {
}

Contract::Contract(int id,
    const Date& created,
    Employee* author,
    Client* client,
    const Date& startDate,
    const Date& endDate,
    double amount)
    : Document(id, created, author),
    client(client),
    project(nullptr),
    startDate(startDate),
    endDate(endDate),
    amount(amount),
    termsText("") {
}

Client* Contract::getClient() const { return client; }
RepairProject* Contract::getProject() const { return project; }
const Date& Contract::getStartDate() const { return startDate; }
const Date& Contract::getEndDate() const { return endDate; }
double Contract::getAmount() const { return amount; }
const string& Contract::getTermsText() const { return termsText; }

void Contract::setProject(RepairProject* value) { project = value; }
void Contract::setStartDate(const Date& value) { startDate = value; }
void Contract::setEndDate(const Date& value) { endDate = value; }
void Contract::setAmount(double value) { amount = value; }
void Contract::setTermsText(const string& value) { termsText = value; }

void Contract::sign() {
    status = "signed";
}

void Contract::terminate() {
    status = "terminated";
}

bool Contract::isActiveOn(const Date& date) const {
    return status == "signed" &&
        !(date < startDate) &&
        !(endDate < date);
}

string Contract::generateSummary() const {
    stringstream ss;
    ss << "Contract #" << id << " amount " << amount;
    if (client) ss << ", client: " << client->getName();
    return ss.str();
}
