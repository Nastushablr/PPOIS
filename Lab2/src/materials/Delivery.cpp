#include "materials/Delivery.h"

using namespace std;

Delivery::Delivery()
    : id(0),
    fromWarehouse(nullptr),
    toWarehouse(nullptr),
    materials(),
    plannedDate(),
    status("planned") {
}

Delivery::Delivery(int id,
    Warehouse* fromWarehouse,
    Warehouse* toWarehouse,
    const Date& plannedDate)
    : id(id),
    fromWarehouse(fromWarehouse),
    toWarehouse(toWarehouse),
    materials(),
    plannedDate(plannedDate),
    status("planned") {
}

int Delivery::getId() const { return id; }
Warehouse* Delivery::getFromWarehouse() const { return fromWarehouse; }
Warehouse* Delivery::getToWarehouse() const { return toWarehouse; }
const Date& Delivery::getPlannedDate() const { return plannedDate; }
const string& Delivery::getStatus() const { return status; }
const vector<Material*>& Delivery::getMaterials() const { return materials; }

void Delivery::setPlannedDate(const Date& value) { plannedDate = value; }
void Delivery::setStatus(const string& value) { status = value; }

void Delivery::addMaterial(Material* material) {
    if (material) materials.push_back(material);
}

void Delivery::start() {
    status = "in_progress";
}

void Delivery::complete() {
    status = "completed";
}
