#include "utils/PriceList.h"

using namespace std;

PriceList::PriceList()
    : name("Default price list"),
    materialMarkupPercent(0.0),
    workBaseRates() {
}

PriceList::PriceList(const string& name, double materialMarkupPercent)
    : name(name),
    materialMarkupPercent(materialMarkupPercent),
    workBaseRates() {
}

const string& PriceList::getName() const { return name; }
double PriceList::getMaterialMarkupPercent() const { return materialMarkupPercent; }

void PriceList::setName(const string& value) { name = value; }

void PriceList::setMaterialMarkupPercent(double value) {
    materialMarkupPercent = value;
}

void PriceList::setWorkRate(int workTypeId, double rate) {
    if (rate < 0.0) rate = 0.0;
    workBaseRates[workTypeId] = rate;
}

bool PriceList::hasWorkRate(int workTypeId) const {
    return workBaseRates.find(workTypeId) != workBaseRates.end();
}

double PriceList::getWorkRate(int workTypeId) const {
    auto it = workBaseRates.find(workTypeId);
    if (it == workBaseRates.end()) return 0.0;
    return it->second;
}

double PriceList::calculateWorkCost(const WorkType* workType, double amount) const {
    if (!workType || amount < 0.0) return 0.0;
    double rate = getWorkRate(workType->getId());
    if (rate <= 0.0) rate = workType->getBaseRate();
    return rate * amount;
}

double PriceList::applyMaterialMarkup(double materialCost) const {
    if (materialCost < 0.0) materialCost = 0.0;
    return materialCost * (1.0 + materialMarkupPercent / 100.0);
}
