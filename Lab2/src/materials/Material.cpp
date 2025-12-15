#include "materials/Material.h"

using namespace std;

Material::Material()
    : id(0),
    name(""),
    unit(""),
    quantity(0),
    unitPrice(0.0),
    supplier("") {
}

Material::Material(int id,
    const string& name,
    const string& unit,
    int quantity,
    double unitPrice,
    const string& supplier)
    : id(id),
    name(name),
    unit(unit),
    quantity(quantity),
    unitPrice(unitPrice),
    supplier(supplier) {
}

int Material::getId() const { return id; }
const string& Material::getName() const { return name; }
const string& Material::getUnit() const { return unit; }
int Material::getQuantity() const { return quantity; }
double Material::getUnitPrice() const { return unitPrice; }
const string& Material::getSupplier() const { return supplier; }

void Material::setName(const string& value) { name = value; }
void Material::setUnit(const string& value) { unit = value; }
void Material::setQuantity(int value) { quantity = value < 0 ? 0 : value; }
void Material::setUnitPrice(double value) { unitPrice = value < 0.0 ? 0.0 : value; }
void Material::setSupplier(const string& value) { supplier = value; }

double Material::getTotalCost() const {
    return quantity * unitPrice;
}

void Material::increaseQuantity(int delta) {
    quantity += delta;
    if (quantity < 0) quantity = 0;
}

bool Material::reserve(int amount) {
    if (amount <= 0) return false;
    if (amount > quantity) return false;
    quantity -= amount;
    return true;
}
