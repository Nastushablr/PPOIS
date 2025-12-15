#include "utils/Schedule.h"

using namespace std;

Schedule::Schedule()
    : tasks() {
}

const vector<Task*>& Schedule::getTasks() const {
    return tasks;
}

void Schedule::addTask(Task* task) {
    if (task) tasks.push_back(task);
}

void Schedule::removeTask(Task* task) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (*it == task) {
            tasks.erase(it);
            break;
        }
    }
}

vector<Task*> Schedule::getTasksForDate(const Date& date) const {
    vector<Task*> result;
    for (auto* t : tasks) {
        if (t && t->getPlannedDate() == date) {
            result.push_back(t);
        }
    }
    return result;
}

int Schedule::countTasksByStatus(const string& status) const {
    int count = 0;
    for (auto* t : tasks) {
        if (t && t->getStatus() == status) ++count;
    }
    return count;
}
