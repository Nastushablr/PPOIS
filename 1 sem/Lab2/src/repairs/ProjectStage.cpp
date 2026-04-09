#include "repairs/ProjectStage.h"

using namespace std;

ProjectStage::ProjectStage()
    : id(0),
    name(""),
    startDate(),
    endDate(),
    progress(0) {
}

ProjectStage::ProjectStage(int id,
    const string& name,
    const Date& startDate,
    const Date& endDate)
    : id(id),
    name(name),
    startDate(startDate),
    endDate(endDate),
    progress(0) {
}

int ProjectStage::getId() const { return id; }
const string& ProjectStage::getName() const { return name; }
const Date& ProjectStage::getStartDate() const { return startDate; }
const Date& ProjectStage::getEndDate() const { return endDate; }
int ProjectStage::getProgress() const { return progress; }

void ProjectStage::setName(const string& value) { name = value; }
void ProjectStage::setStartDate(const Date& value) { startDate = value; }
void ProjectStage::setEndDate(const Date& value) { endDate = value; }

void ProjectStage::setProgress(int value) {
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    progress = value;
}

bool ProjectStage::isCompleted() const {
    return progress >= 100;
}
