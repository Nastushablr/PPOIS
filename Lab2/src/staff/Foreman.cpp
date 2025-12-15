#include "staff/Foreman.h"
#include <iostream>

using namespace std;

Foreman::Foreman()
    : RepairSpecialist(),
    teamSize(0),
    finishedProjects(0) {
    specialization = "foreman";
}

Foreman::Foreman(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary)
    : RepairSpecialist(id, person, hireDate, baseSalary, "foreman"),
    teamSize(0),
    finishedProjects(0) {
}

int Foreman::getTeamSize() const { return teamSize; }
int Foreman::getFinishedProjects() const { return finishedProjects; }

void Foreman::setTeamSize(int value) { teamSize = value < 0 ? 0 : value; }

void Foreman::registerFinishedProject() {
    ++finishedProjects;
}

void Foreman::planSchedule() {
    cout << "Foreman plans work schedule" << endl;
}

string Foreman::getRole() const {
    return "Foreman";
}
