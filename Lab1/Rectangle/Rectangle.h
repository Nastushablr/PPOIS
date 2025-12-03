#pragma once
#include <iostream>

class Rectangle {
private:
    int x1, y1, x2, y2;

public:
    Rectangle(int x1, int y1, int x2, int y2);

    void printCoords() const;
    void move(int dx, int dy);
    void resize(int dwidth, int dheight);

    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Rectangle& r);
    friend std::istream& operator>>(std::istream& in, Rectangle& r);

    Rectangle& operator++();
    Rectangle operator++(int);
    Rectangle& operator--();
    Rectangle operator--(int);
    Rectangle operator+(const Rectangle& other) const;
    Rectangle operator-(const Rectangle& other) const;
    Rectangle& operator+=(const Rectangle& other);
    Rectangle& operator-=(const Rectangle& other);

    int getX1() const { return x1; };
    int getY1() const { return y1; };
    int getX2() const { return x2; };
    int getY2() const { return y2; };
};
