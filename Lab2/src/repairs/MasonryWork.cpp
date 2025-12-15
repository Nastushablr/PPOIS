#include "repairs/MasonryWork.h"

using namespace std;

MasonryWork::MasonryWork()
    : WorkType(0, "Masonry work", 0.0, "m2", "Brick / block work"),
    wallThickness(0.2),
    requiresScaffolding(false) {
}

MasonryWork::MasonryWork(int id,
    double baseRate,
    double wallThickness,
    bool requiresScaffolding)
    : WorkType(id, "Masonry work", baseRate, "m2", "Brick / block work"),
    wallThickness(wallThickness),
    requiresScaffolding(requiresScaffolding) {
}

double MasonryWork::getWallThickness() const { return wallThickness; }
bool MasonryWork::getRequiresScaffolding() const { return requiresScaffolding; }

void MasonryWork::setWallThickness(double value) { wallThickness = value; }
void MasonryWork::setRequiresScaffolding(bool value) { requiresScaffolding = value; }

double MasonryWork::calculateCost(double area) const {
    if (area < 0.0) area = 0.0;
    double coef = 1.0 + (wallThickness - 0.2);
    if (requiresScaffolding) coef += 0.2;
    if (coef < 0.5) coef = 0.5;
    return baseRate * area * coef;
}
