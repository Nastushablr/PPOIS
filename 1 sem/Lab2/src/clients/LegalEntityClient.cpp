#include "clients/LegalEntityClient.h"
#include <sstream>

using namespace std;

LegalEntityClient::LegalEntityClient()
    : Client(),
    companyName(""),
    taxId(""),
    registrationNumber(""),
    director(nullptr),
    bankAccount(""),
    isVatPayer(false) {
}

LegalEntityClient::LegalEntityClient(int id,
    const string& companyName,
    Address* address,
    const Date& registrationDate,
    const string& phone,
    const string& email,
    const string& taxId,
    Person* director)
    : Client(id,
        companyName,
        address,
        registrationDate,
        phone,
        email),
    companyName(companyName),
    taxId(taxId),
    registrationNumber(""),
    director(director),
    bankAccount(""),
    isVatPayer(true) {
}

const string& LegalEntityClient::getCompanyName() const { return companyName; }
const string& LegalEntityClient::getTaxId() const { return taxId; }
const string& LegalEntityClient::getRegistrationNumber() const { return registrationNumber; }
Person* LegalEntityClient::getDirector() const { return director; }
const string& LegalEntityClient::getBankAccount() const { return bankAccount; }
bool LegalEntityClient::getIsVatPayer() const { return isVatPayer; }

void LegalEntityClient::setCompanyName(const string& value) {
    companyName = value;
    name = value;
}

void LegalEntityClient::setTaxId(const string& value) { taxId = value; }
void LegalEntityClient::setRegistrationNumber(const string& value) { registrationNumber = value; }
void LegalEntityClient::setDirector(Person* value) { director = value; }
void LegalEntityClient::setBankAccount(const string& value) { bankAccount = value; }
void LegalEntityClient::setIsVatPayer(bool value) { isVatPayer = value; }

bool LegalEntityClient::validateTaxId() const {
    return !taxId.empty() && taxId.size() >= 9 && taxId.size() <= 12;
}

string LegalEntityClient::getSummaryInfo() const {
    stringstream ss;
    ss << companyName << " (УНП: " << taxId << ")";
    if (director) {
        ss << ", директор: " << director->getFullName();
    }
    return ss.str();
}
