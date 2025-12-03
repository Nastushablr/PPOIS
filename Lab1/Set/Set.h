#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Set {
private:
    struct Element {
        bool isSet;
        string value;
        Set* subset;
    };

    vector<Element> data;

public:
    bool containsElement(const string& v) const;
    Set();
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();

    explicit Set(const string& text);

    static bool IsValidString(const string& text);
    bool isEmpty() const;
    void addElement(const string& value);
    void addSet(const Set& s);
    bool removeElement(const string& value);
    int  size() const;

    bool operator[](const string& value) const;

    Set  operator+(const Set& other) const;
    Set& operator+=(const Set& other);
    Set  operator*(const Set& other) const;
    Set& operator*=(const Set& other);
    Set  operator-(const Set& other) const;
    Set& operator-=(const Set& other);

    Set powerSet() const;

    friend ostream& operator<<(ostream& out, const Set& s);
    friend istream& operator>>(istream& in, Set& s);
};
