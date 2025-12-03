#include "Set.h"
#include <cctype>
#include <algorithm>

using namespace std;

Set::Set() {}

Set::Set(const Set& other) {
    *this = other;
}

Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;

    for (auto& e : data) {
        if (e.isSet) delete e.subset;
    }
    data.clear();

    for (const auto& e : other.data) {
        Element ne;
        ne.isSet = e.isSet;
        if (e.isSet) {
            ne.subset = new Set(*e.subset);
        }
        else {
            ne.value = e.value;
            ne.subset = nullptr;
        }
        data.push_back(ne);
    }
    return *this;
}

Set::~Set() {
    for (auto& e : data) {
        if (e.isSet) delete e.subset;
    }
}

static string trim(const string& s) {
    size_t i = 0;
    while (i < s.size() && isspace(static_cast<unsigned char>(s[i]))) ++i;
    size_t j = s.size();
    while (j > i && isspace(static_cast<unsigned char>(s[j - 1]))) --j;
    return s.substr(i, j - i);
}


Set::Set(const string& text) {
    string s = trim(text);
    if (s.empty()) return;
    if (s.front() == '{' && s.back() == '}')
        s = s.substr(1, s.size() - 2);

    int level = 0;
    string token;
    for (char c : s) {
        if (c == '{') {
            level++;
            token += c;
        }
        else if (c == '}') {
            level--;
            token += c;
        }
        else if (c == ',' && level == 0) {
            string t = trim(token);
            if (!t.empty()) {
                if (t.front() == '{')
                    addSet(Set(t));
                else
                    addElement(t);
            }
            token.clear();
        }
        else {
            token += c;
        }
    }
    string t = trim(token);
    if (!t.empty()) {
        if (t.front() == '{')
            addSet(Set(t));
        else
            addElement(t);
    }
}

bool Set::IsValidString(const string& text) {
    string s = trim(text);
    if (s.size() < 2 || s.front() != '{' || s.back() != '}')
        return false;

    int level = 0;
    for (char c : s) {
        if (c == '{') level++;
        else if (c == '}') {
            level--;
            if (level < 0) return false;
        }
    }
    return level == 0;
}

bool Set::isEmpty() const {
    return data.empty();
}

void Set::addElement(const string& value) {
    for (const auto& e : data)
        if (!e.isSet && e.value == value) return;
    Element el{ false, value, nullptr };
    data.push_back(el);
}

void Set::addSet(const Set& s) {
    Element el;
    el.isSet = true;
    el.subset = new Set(s);
    data.push_back(el);
}

bool Set::removeElement(const string& value) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (!data[i].isSet && data[i].value == value) {
            data.erase(data.begin() + i);
            return true;
        }
    }
    return false;
}

int Set::size() const {
    return (int)data.size();
}

bool Set::operator[](const string& value) const {
    for (const auto& e : data)
        if (!e.isSet && e.value == value) return true;
    return false;
}

bool Set::containsElement(const string& v) const {
    for (const auto& e : data)
        if (!e.isSet && e.value == v) return true;
    return false;
}

Set Set::operator+(const Set& other) const {
    Set res = *this;
    for (const auto& e : other.data) {
        if (!e.isSet)
            res.addElement(e.value);
        else
            res.addSet(*e.subset);
    }
    return res;
}

Set& Set::operator+=(const Set& other) {
    *this = *this + other;
    return *this;
}

Set Set::operator*(const Set& other) const {
    Set res;
    for (const auto& e : data)
        if (!e.isSet && other.containsElement(e.value))
            res.addElement(e.value);
    return res;
}

Set& Set::operator*=(const Set& other) {
    *this = *this * other;
    return *this;
}

Set Set::operator-(const Set& other) const {
    Set res;
    for (const auto& e : data)
        if (!e.isSet && !other.containsElement(e.value))
            res.addElement(e.value);
    return res;
}

Set& Set::operator-=(const Set& other) {
    *this = *this - other;
    return *this;
}

Set Set::powerSet() const {
    Set result;
    vector<string> elems;
    for (const auto& e : data)
        if (!e.isSet) elems.push_back(e.value);
    int m = (int)elems.size();
    int subsets = 1 << m;
    for (int mask = 0; mask < subsets; ++mask) {
        Set subset;
        for (int i = 0; i < m; ++i)
            if (mask & (1 << i))
                subset.addElement(elems[i]);
        result.addSet(subset);
    }
    return result;
}

ostream& operator<<(ostream& out, const Set& s) {
    out << "{";
    for (size_t i = 0; i < s.data.size(); ++i) {
        const auto& e = s.data[i];
        if (e.isSet) out << *e.subset;
        else out << e.value;
        if (i + 1 < s.data.size()) out << ",";
    }
    out << "}";
    return out;
}

istream& operator>>(istream& in, Set& s) {
    string line;
    while (true) {
        cout << "Введите множество в виде {a,b,{a,b}}: ";
        in >> line;
        if (Set::IsValidString(line)) {
            s = Set(line);
            break;
        }
        else {
            cout << "Неверный формат множества, попробуйте ещё раз." << endl;
        }
    }
    return in;
}

