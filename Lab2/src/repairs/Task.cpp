#include "repairs/Task.h"
#include "repairs/RepairProject.h"

using namespace std;

Task::Task()
    : id(0),
    project(nullptr),
    specialist(nullptr),
    workType(nullptr),
    description(""),
    status("planned"),
    priority(1),
    plannedDate(),
    completedDate() {
}

Task::Task(int id,
    RepairProject* project,
    RepairSpecialist* specialist,
    WorkType* workType,
    const string& description,
    int priority,
    const Date& plannedDate)
    : id(id),
    project(project),
    specialist(specialist),
    workType(workType),
    description(description),
    status("planned"),
    priority(priority),
    plannedDate(plannedDate),
    completedDate() {
}

int Task::getId() const { return id; }
RepairProject* Task::getProject() const { return project; }
RepairSpecialist* Task::getSpecialist() const { return specialist; }
WorkType* Task::getWorkType() const { return workType; }
const string& Task::getDescription() const { return description; }
const string& Task::getStatus() const { return status; }
int Task::getPriority() const { return priority; }
const Date& Task::getPlannedDate() const { return plannedDate; }
const Date& Task::getCompletedDate() const { return completedDate; }

void Task::setSpecialist(RepairSpecialist* value) { specialist = value; }
void Task::setWorkType(WorkType* value) { workType = value; }
void Task::setDescription(const string& value) { description = value; }
void Task::setPriority(int value) {
    if (value < 1) value = 1;
    if (value > 5) value = 5;
    priority = value;
}
void Task::setPlannedDate(const Date& value) { plannedDate = value; }

void Task::start() {
    status = "in_progress";
}

void Task::complete(const Date& date) {
    status = "done";
    completedDate = date;
}

bool Task::isCompleted() const {
    return status == "done";
}
