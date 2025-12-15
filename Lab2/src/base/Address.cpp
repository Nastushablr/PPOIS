#include "Address.h"

Address::Address()
    : street(""),
    city(""),
    postalCode(""),
    country(""),
    building(""),
    apartment("") {
}

Address::Address(const string& street,
    const string& city,
    const string& postalCode,
    const string& country,
    const string& building,
    const string& apartment)
    : street(street),
    city(city),
    postalCode(postalCode),
    country(country),
    building(building),
    apartment(apartment) {
}

const string& Address::getStreet() const { return street; }
const string& Address::getCity() const { return city; }
const string& Address::getPostalCode() const { return postalCode; }
const string& Address::getCountry() const { return country; }
const string& Address::getBuilding() const { return building; }
const string& Address::getApartment() const { return apartment; }

void Address::setStreet(const string& value) { street = value; }
void Address::setCity(const string& value) { city = value; }
void Address::setPostalCode(const string& value) { postalCode = value; }
void Address::setCountry(const string& value) { country = value; }
void Address::setBuilding(const string& value) { building = value; }
void Address::setApartment(const string& value) { apartment = value; }

string Address::getFullAddress() const {
    string result = street;
    if (!building.empty()) result += ", " + building;
    if (!apartment.empty()) result += ", apt. " + apartment;
    result += ", " + city + " " + postalCode + ", " + country;
    return result;
}

bool Address::isValid() const {
    return !street.empty() && !city.empty() && !postalCode.empty() && !country.empty();
}

bool Address::validatePostalCode() const {
    return postalCode.size() >= 4 && postalCode.size() <= 10;
}
