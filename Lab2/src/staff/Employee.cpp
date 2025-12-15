#include "staff/Employee.h"

using namespace std;

Employee::Employee()
    : id(0),
    person(nullptr),
    hireDate(),
    baseSalary(0.0),
    position(""),
    status("new") {
}

Employee::Employee(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    const string& position)
    : id(id),
    person(person),
    hireDate(hireDate),
    baseSalary(baseSalary),
    position(position),
    status("active") {
}

int Employee::getId() const { return id; }
Person* Employee::getPerson() const { return person; }
const Date& Employee::getHireDate() const { return hireDate; }
double Employee::getBaseSalary() const { return baseSalary; }
const string& Employee::getPosition() const { return position; }
const string& Employee::getStatus() const { return status; }

void Employee::setPerson(Person* value) { person = value; }
void Employee::setHireDate(const Date& value) { hireDate = value; }
void Employee::setBaseSalary(double value) { baseSalary = value; }
void Employee::setPosition(const string& value) { position = value; }
void Employee::setStatus(const string& value) { status = value; }

void Employee::hire() { status = "active"; }
void Employee::dismiss() { status = "dismissed"; }
void Employee::sendToLeave() { status = "on_leave"; }

int Employee::getExperienceYears(const Date& today) const {
    int years = today.getYear() - hireDate.getYear();
    if (today.getMonth() < hireDate.getMonth() ||
        (today.getMonth() == hireDate.getMonth() &&
            today.getDay() < hireDate.getDay())) {
        years--;
    }
    return years;
}

double Employee::calculateMonthlySalary() const {
    return baseSalary;
}
