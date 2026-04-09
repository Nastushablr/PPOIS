#include "repairs/WorkType.h"

using namespace std;

WorkType::WorkType()
    : id(0),
    name(""),
    baseRate(0.0),
    unit(""),
    description("") {
}

WorkType::WorkType(int id,
    const string& name,
    double baseRate,
    const string& unit,
    const string& description)
    : id(id),
    name(name),
    baseRate(baseRate),
    unit(unit),
    description(description) {
}

int WorkType::getId() const { return id; }
const string& WorkType::getName() const { return name; }
double WorkType::getBaseRate() const { return baseRate; }
const string& WorkType::getUnit() const { return unit; }
const string& WorkType::getDescription() const { return description; }

void WorkType::setName(const string& value) { name = value; }
void WorkType::setBaseRate(double value) { baseRate = value < 0.0 ? 0.0 : value; }
void WorkType::setUnit(const string& value) { unit = value; }
void WorkType::setDescription(const string& value) { description = value; }
