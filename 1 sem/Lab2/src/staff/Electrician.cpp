#include "staff/Electrician.h"
#include <iostream>

using namespace std;

Electrician::Electrician()
    : RepairSpecialist(),
    hasHighVoltagePermit(false),
    safetyChecksDone(0) {
    specialization = "electrician";
}

Electrician::Electrician(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    bool highVoltagePermit)
    : RepairSpecialist(id, person, hireDate, baseSalary, "electrician"),
    hasHighVoltagePermit(highVoltagePermit),
    safetyChecksDone(0) {
}

bool Electrician::getHasHighVoltagePermit() const { return hasHighVoltagePermit; }
int Electrician::getSafetyChecksDone() const { return safetyChecksDone; }

void Electrician::setHasHighVoltagePermit(bool value) {
    hasHighVoltagePermit = value;
}

void Electrician::performRepair() {
    registerCompletedTask();
    cout << "Electrician performs repair" << endl;
}

void Electrician::performSafetyCheck() {
    ++safetyChecksDone;
    cout << "Electrician performs safety check" << endl;
}

string Electrician::getRole() const {
    return "Electrician";
}
