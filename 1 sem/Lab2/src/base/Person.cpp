#include "Person.h"


Person::Person()
    : id(0),
    firstName(""),
    lastName(""),
    birthDate(),
    phone(""),
    email(""),
    passportNumber(""),
    nationality("") {
}

Person::Person(int id,
    const string& firstName,
    const string& lastName,
    const Date& birthDate,
    const string& phone,
    const string& email,
    const string& passportNumber,
    const string& nationality)
    : id(id),
    firstName(firstName),
    lastName(lastName),
    birthDate(birthDate),
    phone(phone),
    email(email),
    passportNumber(passportNumber),
    nationality(nationality) {
}

int Person::getId() const { return id; }
const string& Person::getFirstName() const { return firstName; }
const string& Person::getLastName() const { return lastName; }
const Date& Person::getBirthDate() const { return birthDate; }
const string& Person::getPhone() const { return phone; }
const string& Person::getEmail() const { return email; }
const string& Person::getPassportNumber() const { return passportNumber; }
const string& Person::getNationality() const { return nationality; }

void Person::setFirstName(const string& value) { firstName = value; }
void Person::setLastName(const string& value) { lastName = value; }
void Person::setBirthDate(const Date& value) { birthDate = value; }
void Person::setPhone(const string& value) { phone = value; }
void Person::setEmail(const string& value) { email = value; }
void Person::setPassportNumber(const string& value) { passportNumber = value; }
void Person::setNationality(const string& value) { nationality = value; }

string Person::getFullName() const {
    return firstName + " " + lastName;
}

int Person::getAge(const Date& today) const {
    int age = today.getYear() - birthDate.getYear();
    if (today.getMonth() < birthDate.getMonth() ||
        (today.getMonth() == birthDate.getMonth() &&
            today.getDay() < birthDate.getDay())) {
        age--;
    }
    return age;
}

bool Person::validateEmail() const {
    auto atPos = email.find('@');
    auto dotPos = email.find('.', atPos == string::npos ? 0 : atPos);
    return atPos != string::npos && dotPos != string::npos && atPos < dotPos;
}

void Person::updateContact(const string& newPhone,
    const string& newEmail) {
    phone = newPhone;
    email = newEmail;
}
