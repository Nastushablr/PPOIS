#include "materials/Warehouse.h"

using namespace std;

Warehouse::Warehouse()
    : id(0),
    address(nullptr),
    maxValue(0.0),
    materials(),
    tools() {
}

Warehouse::Warehouse(int id, Address* address, double maxValue)
    : id(id),
    address(address),
    maxValue(maxValue),
    materials(),
    tools() {
}

int Warehouse::getId() const { return id; }
Address* Warehouse::getAddress() const { return address; }
double Warehouse::getMaxValue() const { return maxValue; }

const vector<Material*>& Warehouse::getMaterials() const { return materials; }
const vector<Tool*>& Warehouse::getTools() const { return tools; }

void Warehouse::addMaterial(Material* material) {
    if (material) materials.push_back(material);
}

void Warehouse::addTool(Tool* tool) {
    if (tool) tools.push_back(tool);
}

Material* Warehouse::findMaterialByName(const string& name) const {
    for (auto* m : materials) {
        if (m && m->getName() == name) return m;
    }
    return nullptr;
}

Tool* Warehouse::findToolByName(const string& name) const {
    for (auto* t : tools) {
        if (t && t->getName() == name) return t;
    }
    return nullptr;
}

double Warehouse::calculateTotalValue() const {
    double sum = 0.0;
    for (auto* m : materials) {
        if (m) sum += m->getTotalCost();
    }
    for (auto* t : tools) {
        if (t) sum += t->getQuantity() * 100.0;
    }
    return sum;
}
