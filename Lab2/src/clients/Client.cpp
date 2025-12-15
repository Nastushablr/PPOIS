#include "clients/Client.h"

using namespace std;

Client::Client()
    : id(0),
    name(""),
    address(nullptr),
    registrationDate(),
    phone(""),
    email(""),
    status("new"),
    totalSpent(0.0) {
}

Client::Client(int id,
    const string& name,
    Address* address,
    const Date& registrationDate,
    const string& phone,
    const string& email)
    : id(id),
    name(name),
    address(address),
    registrationDate(registrationDate),
    phone(phone),
    email(email),
    status("new"),
    totalSpent(0.0) {
}

int Client::getId() const { return id; }
const string& Client::getName() const { return name; }
Address* Client::getAddress() const { return address; }
const Date& Client::getRegistrationDate() const { return registrationDate; }
const string& Client::getPhone() const { return phone; }
const string& Client::getEmail() const { return email; }
const string& Client::getStatus() const { return status; }
double Client::getTotalSpent() const { return totalSpent; }

void Client::setName(const string& value) { name = value; }
void Client::setAddress(Address* value) { address = value; }
void Client::setPhone(const string& value) { phone = value; }
void Client::setEmail(const string& value) { email = value; }
void Client::setStatus(const string& value) { status = value; }

void Client::registerClient() {
    status = "active";
}

void Client::deactivate() {
    status = "inactive";
}

void Client::block() {
    status = "blocked";
}

void Client::updateContacts(const string& newPhone,
    const string& newEmail) {
    phone = newPhone;
    email = newEmail;
}

void Client::addSpent(double amount) {
    if (amount > 0.0) {
        totalSpent += amount;
    }
}
