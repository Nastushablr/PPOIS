#include "staff/HRSpecialist.h"
#include <iostream>

using namespace std;

HRSpecialist::HRSpecialist()
    : Employee(),
    hiredEmployees(0),
    interviewsCount(0) {
}

HRSpecialist::HRSpecialist(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary)
    : Employee(id, person, hireDate, baseSalary, "HR Specialist"),
    hiredEmployees(0),
    interviewsCount(0) {
}

int HRSpecialist::getHiredEmployees() const { return hiredEmployees; }
int HRSpecialist::getInterviewsCount() const { return interviewsCount; }

void HRSpecialist::registerInterview() {
    ++interviewsCount;
}

void HRSpecialist::hireNewEmployee() {
    ++hiredEmployees;
    cout << "HR hired new employee" << endl;
}

double HRSpecialist::calculateMonthlySalary() const {
    return baseSalary + hiredEmployees * 30.0;
}

string HRSpecialist::getRole() const {
    return "HR Specialist";
}
