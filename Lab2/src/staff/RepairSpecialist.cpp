#include "staff/RepairSpecialist.h"

using namespace std;

RepairSpecialist::RepairSpecialist()
    : Employee(),
    specialization(""),
    completedTasks(0),
    skillLevel(1) {
}

RepairSpecialist::RepairSpecialist(int id,
    Person* person,
    const Date& hireDate,
    double baseSalary,
    const string& specialization)
    : Employee(id, person, hireDate, baseSalary, "Repair Specialist"),
    specialization(specialization),
    completedTasks(0),
    skillLevel(1) {
}

int RepairSpecialist::getCompletedTasks() const { return completedTasks; }
int RepairSpecialist::getSkillLevel() const { return skillLevel; }
const string& RepairSpecialist::getSpecialization() const { return specialization; }

void RepairSpecialist::increaseSkill() {
    if (skillLevel < 5) ++skillLevel;
}

void RepairSpecialist::registerCompletedTask() {
    ++completedTasks;
}

double RepairSpecialist::calculateMonthlySalary() const {
    return baseSalary + completedTasks * 20.0 + skillLevel * 50.0;
}
