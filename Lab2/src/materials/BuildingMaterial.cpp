#include "materials/BuildingMaterial.h"

using namespace std;

BuildingMaterial::BuildingMaterial()
    : Material(),
    strengthClass(""),
    forOutdoorUse(false),
    density(0.0) {
}

BuildingMaterial::BuildingMaterial(int id,
    const string& name,
    const string& unit,
    int quantity,
    double unitPrice,
    const string& supplier,
    const string& strengthClass,
    bool forOutdoorUse,
    double density)
    : Material(id, name, unit, quantity, unitPrice, supplier),
    strengthClass(strengthClass),
    forOutdoorUse(forOutdoorUse),
    density(density) {
}

const string& BuildingMaterial::getStrengthClass() const { return strengthClass; }
bool BuildingMaterial::isForOutdoorUse() const { return forOutdoorUse; }
double BuildingMaterial::getDensity() const { return density; }

void BuildingMaterial::setStrengthClass(const string& value) { strengthClass = value; }
void BuildingMaterial::setForOutdoorUse(bool value) { forOutdoorUse = value; }
void BuildingMaterial::setDensity(double value) { density = value; }

double BuildingMaterial::getTotalCost() const {
    double coef = (density > 0.0 && density < 800.0) ? 1.0 : 1.1;
    return Material::getTotalCost() * coef;
}
