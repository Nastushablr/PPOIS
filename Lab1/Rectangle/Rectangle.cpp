#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
}

void Rectangle::printCoords() const {
    cout << "Координаты вершин: (" << x1 << ", " << y1 << ") и (" << x2 << ", " << y2 << ")" << endl;
}

void Rectangle::move(int dx, int dy) {
    x1 += dx; y1 += dy; x2 += dx; y2 += dy;
}

void Rectangle::resize(int dwidth, int dheight) {
    x2 += dwidth; y2 += dheight;
}

bool Rectangle::operator==(const Rectangle& o) const {
    return x1 == o.x1 && y1 == o.y1 && x2 == o.x2 && y2 == o.y2;
}

bool Rectangle::operator!=(const Rectangle& o) const {
    return !(*this == o);
}

ostream& operator<<(ostream& out, const Rectangle& r) {
    out << "Rectangle((" << r.x1 << "," << r.y1 << "),(" << r.x2 << "," << r.y2 << "))";
    return out;
}

istream& operator>>(istream& in, Rectangle& r) {
    cout << "Введите координаты x1 y1 x2 y2: ";
    in >> r.x1 >> r.y1 >> r.x2 >> r.y2;
    return in;
}

Rectangle& Rectangle::operator++() {
    resize(1, 1);
    return *this;
}
Rectangle Rectangle::operator++(int) {
    Rectangle temp = *this;
    resize(1, 1);
    return temp;
}
Rectangle& Rectangle::operator--() {
    resize(-1, -1);
    return *this;
}
Rectangle Rectangle::operator--(int) {
    Rectangle temp = *this;
    resize(-1, -1);
    return temp;
}


Rectangle Rectangle::operator+(const Rectangle& o) const {
    int nx1 = min(x1, o.x1), ny1 = min(y1, o.y1);
    int nx2 = max(x2, o.x2), ny2 = max(y2, o.y2);
    return Rectangle(nx1, ny1, nx2, ny2);
}

Rectangle Rectangle::operator-(const Rectangle& o) const {
    int nx1 = max(x1, o.x1), ny1 = max(y1, o.y1);
    int nx2 = min(x2, o.x2), ny2 = min(y2, o.y2);
    if (nx1 > nx2 || ny1 > ny2) return Rectangle(0, 0, 0, 0);
    return Rectangle(nx1, ny1, nx2, ny2);
}

Rectangle& Rectangle::operator+=(const Rectangle& o) {
    *this = *this + o;
    return *this;
}
Rectangle& Rectangle::operator-=(const Rectangle& o) {
    *this = *this - o;
    return *this;
}

