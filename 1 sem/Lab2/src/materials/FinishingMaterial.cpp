#include "materials/FinishingMaterial.h"

using namespace std;

FinishingMaterial::FinishingMaterial()
    : Material(),
    color(""),
    finishType(""),
    coverage(0.0) {
}

FinishingMaterial::FinishingMaterial(int id,
    const string& name,
    const string& unit,
    int quantity,
    double unitPrice,
    const string& supplier,
    const string& color,
    const string& finishType,
    double coverage)
    : Material(id, name, unit, quantity, unitPrice, supplier),
    color(color),
    finishType(finishType),
    coverage(coverage) {
}

const string& FinishingMaterial::getColor() const { return color; }
const string& FinishingMaterial::getFinishType() const { return finishType; }
double FinishingMaterial::getCoverage() const { return coverage; }

void FinishingMaterial::setColor(const string& value) { color = value; }
void FinishingMaterial::setFinishType(const string& value) { finishType = value; }
void FinishingMaterial::setCoverage(double value) { coverage = value; }

double FinishingMaterial::getCoverableArea() const {
    return quantity * coverage;
}
