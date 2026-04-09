#include "clients/PrivateClient.h"

using namespace std;

PrivateClient::PrivateClient()
    : Client(),
    person(nullptr),
    maritalStatus("unknown"),
    dependents(0) {
}

PrivateClient::PrivateClient(int id,
    Person* person,
    Address* address,
    const Date& registrationDate,
    const string& phone,
    const string& email)
    : Client(id,
        person ? person->getFullName() : string(""),
        address,
        registrationDate,
        phone,
        email),
    person(person),
    maritalStatus("single"),
    dependents(0) {
}

Person* PrivateClient::getPerson() const { return person; }
const string& PrivateClient::getMaritalStatus() const { return maritalStatus; }
int PrivateClient::getDependents() const { return dependents; }

void PrivateClient::setPerson(Person* value) {
    person = value;
    if (person) {
        name = person->getFullName();
    }
}

void PrivateClient::setMaritalStatus(const string& value) {
    maritalStatus = value;
}

void PrivateClient::setDependents(int value) {
    dependents = (value < 0) ? 0 : value;
}

bool PrivateClient::hasValidPassport() const {
    return person && !person->getPassportNumber().empty();
}

int PrivateClient::getAge(const Date& today) const {
    return person ? person->getAge(today) : 0;
}
