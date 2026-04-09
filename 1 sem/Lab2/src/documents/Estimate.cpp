#include "documents/Estimate.h"
#include <sstream>

using namespace std;

Estimate::Estimate()
    : Document(),
    project(nullptr),
    materials(),
    laborCost(0.0),
    totalAmount(0.0),
    validUntil() {
}

Estimate::Estimate(int id,
    const Date& created,
    Employee* author,
    RepairProject* project)
    : Document(id, created, author),
    project(project),
    materials(),
    laborCost(0.0),
    totalAmount(0.0),
    validUntil() {
}

RepairProject* Estimate::getProject() const { return project; }
const vector<Material*>& Estimate::getMaterials() const { return materials; }
double Estimate::getLaborCost() const { return laborCost; }
double Estimate::getTotalAmount() const { return totalAmount; }
const Date& Estimate::getValidUntil() const { return validUntil; }

void Estimate::setLaborCost(double value) { laborCost = value; }
void Estimate::setValidUntil(const Date& value) { validUntil = value; }

void Estimate::addMaterial(Material* material) {
    if (material) materials.push_back(material);
}

void Estimate::clearMaterials() {
    materials.clear();
}

void Estimate::calculateTotal() {
    totalAmount = laborCost;
    for (auto* m : materials) {
        if (m) totalAmount += m->getTotalCost();
    }
}

bool Estimate::isExpired(const Date& today) const {
    return !(today < validUntil) && !(today == validUntil);
}

string Estimate::generateSummary() const {
    stringstream ss;
    ss << "Estimate #" << id << " total " << totalAmount;
    return ss.str();
}
