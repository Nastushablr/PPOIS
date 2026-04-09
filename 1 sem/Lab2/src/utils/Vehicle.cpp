#include "utils/Vehicle.h"

using namespace std;

Vehicle::Vehicle()
    : id(0),
    plateNumber(""),
    model(""),
    fuelConsumptionPer100km(0.0),
    driver(nullptr),
    lastServiceDate(),
    mileage(0.0) {
}

Vehicle::Vehicle(int id,
    const string& plateNumber,
    const string& model,
    double fuelConsumptionPer100km,
    Employee* driver,
    const Date& lastServiceDate,
    double mileage)
    : id(id),
    plateNumber(plateNumber),
    model(model),
    fuelConsumptionPer100km(fuelConsumptionPer100km),
    driver(driver),
    lastServiceDate(lastServiceDate),
    mileage(mileage) {
}

int Vehicle::getId() const { return id; }
const string& Vehicle::getPlateNumber() const { return plateNumber; }
const string& Vehicle::getModel() const { return model; }
double Vehicle::getFuelConsumptionPer100km() const { return fuelConsumptionPer100km; }
Employee* Vehicle::getDriver() const { return driver; }
const Date& Vehicle::getLastServiceDate() const { return lastServiceDate; }
double Vehicle::getMileage() const { return mileage; }

void Vehicle::setPlateNumber(const string& value) { plateNumber = value; }
void Vehicle::setModel(const string& value) { model = value; }
void Vehicle::setFuelConsumptionPer100km(double value) {
    fuelConsumptionPer100km = value < 0.0 ? 0.0 : value;
}
void Vehicle::setDriver(Employee* value) { driver = value; }
void Vehicle::setLastServiceDate(const Date& value) { lastServiceDate = value; }
void Vehicle::setMileage(double value) { mileage = value < 0.0 ? 0.0 : value; }

double Vehicle::estimateFuelForDistance(double km) const {
    if (km <= 0.0 || fuelConsumptionPer100km <= 0.0) return 0.0;
    return fuelConsumptionPer100km * km / 100.0;
}

void Vehicle::addTrip(double km) {
    if (km > 0.0) mileage += km;
}
