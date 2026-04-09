#include "documents/ActOfCompletion.h"
#include <sstream>

using namespace std;

ActOfCompletion::ActOfCompletion()
    : Document(),
    project(nullptr),
    completionDate(),
    customerComment(""),
    qualityScore(0) {
}

ActOfCompletion::ActOfCompletion(int id,
    const Date& created,
    Employee* author,
    RepairProject* project,
    const Date& completionDate)
    : Document(id, created, author),
    project(project),
    completionDate(completionDate),
    customerComment(""),
    qualityScore(0) {
}

RepairProject* ActOfCompletion::getProject() const { return project; }
const Date& ActOfCompletion::getCompletionDate() const { return completionDate; }
const string& ActOfCompletion::getCustomerComment() const { return customerComment; }
int ActOfCompletion::getQualityScore() const { return qualityScore; }

void ActOfCompletion::setCompletionDate(const Date& value) { completionDate = value; }
void ActOfCompletion::setCustomerComment(const string& value) { customerComment = value; }
void ActOfCompletion::setQualityScore(int value) {
    if (value < 0) value = 0;
    if (value > 10) value = 10;
    qualityScore = value;
}

void ActOfCompletion::signByCustomer() {
    status = "signed";
}

bool ActOfCompletion::isSigned() const {
    return status == "signed";
}

string ActOfCompletion::generateSummary() const {
    stringstream ss;
    ss << "ActOfCompletion #" << id
        << " quality " << qualityScore;
    return ss.str();
}
