#include "materials/Tool.h"

using namespace std;

Tool::Tool()
    : id(0),
    name(""),
    toolType(""),
    quantity(0),
    condition("good"),
    lastService() {
}

Tool::Tool(int id,
    const string& name,
    const string& toolType,
    int quantity,
    const string& condition,
    const Date& lastService)
    : id(id),
    name(name),
    toolType(toolType),
    quantity(quantity),
    condition(condition),
    lastService(lastService) {
}

int Tool::getId() const { return id; }
const string& Tool::getName() const { return name; }
const string& Tool::getToolType() const { return toolType; }
int Tool::getQuantity() const { return quantity; }
const string& Tool::getCondition() const { return condition; }
const Date& Tool::getLastService() const { return lastService; }

void Tool::setName(const string& value) { name = value; }
void Tool::setToolType(const string& value) { toolType = value; }
void Tool::setQuantity(int value) { quantity = value < 0 ? 0 : value; }
void Tool::setCondition(const string& value) { condition = value; }
void Tool::setLastService(const Date& value) { lastService = value; }

bool Tool::checkout(int amount) {
    if (amount <= 0 || amount > quantity) return false;
    quantity -= amount;
    return true;
}

void Tool::returnBack(int amount) {
    if (amount > 0) quantity += amount;
}

void Tool::markServiced(const Date& date) {
    lastService = date;
    condition = "good";
}
