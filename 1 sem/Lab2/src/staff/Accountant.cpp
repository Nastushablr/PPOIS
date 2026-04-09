#include "staff/Accountant.h"
#include <iostream>

using namespace std;

Accountant::Accountant()
    : Employee(),
    qualificationLevel("junior"),
    closedReports(0) {
}

Accountant::Accountant(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    const string& qualificationLevel)
    : Employee(id, person, hireDate, baseSalary, "Accountant"),
    qualificationLevel(qualificationLevel),
    closedReports(0) {
}

const string& Accountant::getQualificationLevel() const { return qualificationLevel; }
int Accountant::getClosedReports() const { return closedReports; }

void Accountant::setQualificationLevel(const string& value) {
    qualificationLevel = value;
}

void Accountant::createInvoice(double amount) {
    cout << "Accountant creates invoice for " << amount << endl;
}

void Accountant::closeMonthlyReport() {
    ++closedReports;
}

double Accountant::calculateMonthlySalary() const {
    double coef = 1.0;
    if (qualificationLevel == "middle") coef = 1.2;
    else if (qualificationLevel == "senior") coef = 1.5;
    return baseSalary * coef;
}

string Accountant::getRole() const {
    return "Accountant";
}
