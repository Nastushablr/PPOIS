#include "staff/Designer.h"
#include <iostream>

using namespace std;

Designer::Designer()
    : RepairSpecialist(),
    mainStyle("modern"),
    createdDesigns(0) {
    specialization = "designer";
}

Designer::Designer(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    const string& mainStyle)
    : RepairSpecialist(id, person, hireDate, baseSalary, "designer"),
    mainStyle(mainStyle),
    createdDesigns(0) {
}

const string& Designer::getMainStyle() const { return mainStyle; }
int Designer::getCreatedDesigns() const { return createdDesigns; }

void Designer::setMainStyle(const string& value) { mainStyle = value; }

void Designer::createDesign() {
    ++createdDesigns;
    registerCompletedTask();
    cout << "Designer created new design" << endl;
}

string Designer::getRole() const {
    return "Designer";
}
