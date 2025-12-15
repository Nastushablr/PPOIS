#include "repairs/RepairObject.h"

using namespace std;

RepairObject::RepairObject()
    : id(0),
    address(nullptr),
    owner(nullptr),
    objectType("apartment"),
    area(0.0),
    buildYear(2000) {
}

RepairObject::RepairObject(int id,
    Address* address,
    Client* owner,
    const string& objectType,
    double area,
    int buildYear)
    : id(id),
    address(address),
    owner(owner),
    objectType(objectType),
    area(area),
    buildYear(buildYear) {
}

int RepairObject::getId() const { return id; }
Address* RepairObject::getAddress() const { return address; }
Client* RepairObject::getOwner() const { return owner; }
const string& RepairObject::getObjectType() const { return objectType; }
double RepairObject::getArea() const { return area; }
int RepairObject::getBuildYear() const { return buildYear; }

void RepairObject::setAddress(Address* value) { address = value; }
void RepairObject::setOwner(Client* value) { owner = value; }
void RepairObject::setObjectType(const string& value) { objectType = value; }
void RepairObject::setArea(double value) { area = value < 0.0 ? 0.0 : value; }
void RepairObject::setBuildYear(int value) { buildYear = value; }

bool RepairObject::isOldBuilding() const {
    return buildYear > 0 && buildYear <= 1995;
}
