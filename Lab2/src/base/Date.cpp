#include "Date.h"
#include <sstream>
#include <iomanip>


Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!validateDateRange()) {
        day = 1;
        month = 1;
        year = 2000;
    }
}

bool Date::isLeap(int y) const {
    return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}

int Date::daysInMonth(int m, int y) const {
    static const int table[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) return 29;
    if (m >= 1 && m <= 12) return table[m - 1];
    return 0;
}

bool Date::validateDateRange() const {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    return day <= daysInMonth(month, year);
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
    if (!validateDateRange()) {
        day = 1;
        month = 1;
        year = 2000;
    }
}

bool Date::isValid() const {
    return validateDateRange();
}

int Date::daysUntil(const Date& other) const {
    if (*this == other) return 0;

    Date tmp = *this;
    int sign = 1;
    if (other < *this) {
        tmp = other;
        sign = -1;
    }

    int count = 0;
    while (!(tmp == (sign > 0 ? other : *this))) {
        tmp.addDays(1);
        ++count;
    }
    return sign * count;
}

void Date::addDays(int daysToAdd) {
    if (daysToAdd < 0) {
        return;
    }
    day += daysToAdd;
    while (!validateDateRange()) {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "."
        << setw(2) << month << "."
        << year;
    return ss.str();
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}
