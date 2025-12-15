#include "repairs/DesignWork.h"

using namespace std;

DesignWork::DesignWork()
    : WorkType(0, "Design work", 0.0, "hour", "Interior design"),
    complexityLevel(1),
    includes3D(false) {
}

DesignWork::DesignWork(int id,
    double baseRate,
    int complexityLevel,
    bool includes3D)
    : WorkType(id, "Design work", baseRate, "hour", "Interior design"),
    complexityLevel(complexityLevel),
    includes3D(includes3D) {
}

int DesignWork::getComplexityLevel() const { return complexityLevel; }
bool DesignWork::getIncludes3D() const { return includes3D; }

void DesignWork::setComplexityLevel(int value) {
    if (value < 1) value = 1;
    if (value > 5) value = 5;
    complexityLevel = value;
}

void DesignWork::setIncludes3D(bool value) { includes3D = value; }

double DesignWork::calculateCost(double hours) const {
    if (hours < 0.0) hours = 0.0;
    double coef = 1.0 + (complexityLevel - 1) * 0.2;
    if (includes3D) coef += 0.3;
    return baseRate * hours * coef;
}
