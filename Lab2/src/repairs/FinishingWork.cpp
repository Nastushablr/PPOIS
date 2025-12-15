#include "repairs/FinishingWork.h"

using namespace std;

FinishingWork::FinishingWork()
    : WorkType(0, "Finishing work", 0.0, "m2", "Painting / plaster"),
    layersCount(1),
    premiumMaterials(false) {
}

FinishingWork::FinishingWork(int id,
    double baseRate,
    int layersCount,
    bool premiumMaterials)
    : WorkType(id, "Finishing work", baseRate, "m2", "Painting / plaster"),
    layersCount(layersCount),
    premiumMaterials(premiumMaterials) {
}

int FinishingWork::getLayersCount() const { return layersCount; }
bool FinishingWork::getPremiumMaterials() const { return premiumMaterials; }

void FinishingWork::setLayersCount(int value) {
    if (value < 1) value = 1;
    layersCount = value;
}

void FinishingWork::setPremiumMaterials(bool value) { premiumMaterials = value; }

double FinishingWork::calculateCost(double area) const {
    if (area < 0.0) area = 0.0;
    double coef = layersCount;
    if (premiumMaterials) coef *= 1.3;
    return baseRate * area * coef;
}
