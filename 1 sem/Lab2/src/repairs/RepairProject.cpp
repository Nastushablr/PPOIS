#include "repairs/RepairProject.h"
#include "repairs/Task.h"

using namespace std;

RepairProject::RepairProject()
    : id(0),
    client(nullptr),
    object(nullptr),
    startDate(),
    plannedEndDate(),
    budget(0.0),
    status("planned"),
    stages(),
    tasks() {
}

RepairProject::RepairProject(int id,
    Client* client,
    RepairObject* object,
    const Date& startDate,
    double budget)
    : id(id),
    client(client),
    object(object),
    startDate(startDate),
    plannedEndDate(),
    budget(budget),
    status("planned"),
    stages(),
    tasks() {
}

int RepairProject::getId() const { return id; }
Client* RepairProject::getClient() const { return client; }
RepairObject* RepairProject::getObject() const { return object; }
const Date& RepairProject::getStartDate() const { return startDate; }
const Date& RepairProject::getPlannedEndDate() const { return plannedEndDate; }
double RepairProject::getBudget() const { return budget; }
const string& RepairProject::getStatus() const { return status; }

const vector<ProjectStage*>& RepairProject::getStages() const { return stages; }
const vector<Task*>& RepairProject::getTasks() const { return tasks; }

void RepairProject::setPlannedEndDate(const Date& value) { plannedEndDate = value; }
void RepairProject::setBudget(double value) { budget = value < 0.0 ? 0.0 : value; }
void RepairProject::setStatus(const string& value) { status = value; }

void RepairProject::addStage(ProjectStage* stage) {
    if (stage) stages.push_back(stage);
}

void RepairProject::addTask(Task* task) {
    if (task) tasks.push_back(task);
}

double RepairProject::calculateProgress() const {
    if (stages.empty()) return 0.0;
    int sum = 0;
    for (auto* s : stages) {
        if (s) sum += s->getProgress();
    }
    return static_cast<double>(sum) / stages.size();
}

int RepairProject::countOpenTasks() const {
    int count = 0;
    for (auto* t : tasks) {
        if (t && !t->isCompleted()) ++count;
    }
    return count;
}

void RepairProject::start() {
    status = "in_progress";
}

void RepairProject::complete() {
    status = "completed";
}
