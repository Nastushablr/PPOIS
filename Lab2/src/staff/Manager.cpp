#include "staff/Manager.h"
#include <iostream>

using namespace std;

Manager::Manager()
    : Employee(),
    department(""),
    teamSize(0),
    performanceRating(0.0) {
}

Manager::Manager(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    const string& department)
    : Employee(id, person, hireDate, baseSalary, "Manager"),
    department(department),
    teamSize(0),
    performanceRating(0.0) {
}

const string& Manager::getDepartment() const { return department; }
int Manager::getTeamSize() const { return teamSize; }
double Manager::getPerformanceRating() const { return performanceRating; }

void Manager::setDepartment(const string& value) { department = value; }
void Manager::setTeamSize(int value) { teamSize = value < 0 ? 0 : value; }
void Manager::setPerformanceRating(double value) {
    if (value < 0.0) value = 0.0;
    if (value > 10.0) value = 10.0;
    performanceRating = value;
}

void Manager::assignTask(int taskId) {
    cout << "Manager assigns task #" << taskId << endl;
}

void Manager::conductMeeting() {
    cout << "Manager conducts team meeting" << endl;
}

void Manager::addTeamMember() {
    ++teamSize;
}

double Manager::calculateMonthlySalary() const {
    double bonus = teamSize * 50.0 + performanceRating * 100.0;
    return baseSalary + bonus;
}

string Manager::getRole() const {
    return "Manager";
}
