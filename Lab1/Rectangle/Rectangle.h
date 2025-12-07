#pragma once

#include <iostream>

/// Класс прямоугольника на плоскости, заданного координатами левого верхнего (x1,y1) 
/// и правого нижнего (x2,y2) углов.
/**
 * Поддерживает перемещение, изменение размера, сравнение, инкремент/декремент,
 * объединение (+), пересечение (-), ввод/вывод.
 */
class Rectangle {
private:
    int x1, y1, x2, y2; ///< Координаты углов: (x1,y1) - левый верхний, (x2,y2) - правый нижний.

public:
    /**
     * @brief Конструктор по координатам углов.
     * @param x1 X-координата левого верхнего угла
     * @param y1 Y-координата левого верхнего угла
     * @param x2 X-координата правого нижнего угла
     * @param y2 Y-координата правого нижнего угла
     */
    Rectangle(int x1, int y1, int x2, int y2);

    /**
     * @brief Выводит координаты углов в консоль.
     * Формат: "Координаты вершин: (x1, y1) и (x2, y2)"
     */
    void printCoords() const;

    /**
     * @brief Перемещает прямоугольник на вектор (dx, dy).
     * @param dx Смещение по оси X
     * @param dy Смещение по оси Y
     */
    void move(int dx, int dy);

    /**
     * @brief Изменяет размер: ширина += dwidth, высота += dheight.
     * @param dwidth Изменение ширины (x2 += dwidth)
     * @param dheight Изменение высоты (y2 += dheight)
     */
    void resize(int dwidth, int dheight);

    /**
     * @brief Оператор сравнения на равенство.
     * @param other Сравниваемый прямоугольник
     * @return true если все координаты совпадают
     */
    bool operator==(const Rectangle& other) const;

    /**
     * @brief Оператор сравнения на неравенство.
     * @param other Сравниваемый прямоугольник
     * @return true если координаты различаются
     */
    bool operator!=(const Rectangle& other) const;

    /**
     * @brief Оператор вывода в поток.
     * Формат: "Rectangle((x1,y1),(x2,y2))"
     */
    friend std::ostream& operator<<(std::ostream& out, const Rectangle& r);

    /**
     * @brief Оператор ввода из потока.
     * Запрашивает: "Введите координаты x1 y1 x2 y2: "
     */
    friend std::istream& operator>>(std::istream& in, Rectangle& r);

    /**
     * @brief Префиксный инкремент: увеличивает размер на 1x1.
     * @return Ссылка на изменённый объект
     */
    Rectangle& operator++();

    /**
     * @brief Постфиксный инкремент: увеличивает размер на 1x1.
     * @return Копия объекта до изменения
     */
    Rectangle operator++(int);

    /**
     * @brief Префиксный декремент: уменьшает размер на 1x1.
     * @return Ссылка на изменённый объект
     */
    Rectangle& operator--();

    /**
     * @brief Постфиксный декремент: уменьшает размер на 1x1.
     * @return Копия объекта до изменения
     */
    Rectangle operator--(int);

    /**
     * @brief Объединение прямоугольников (минимальный охватывающий).
     * @param other Второй прямоугольник
     * @return Новый прямоугольник-объединение
     */
    Rectangle operator+(const Rectangle& other) const;

    /**
     * @brief Пересечение прямоугольников (пустой если нет пересечения).
     * @param other Второй прямоугольник
     * @return Новый прямоугольник-пересечение или (0,0,0,0)
     */
    Rectangle operator-(const Rectangle& other) const;

    /**
     * @brief Оператор объединения с присваиванием.
     * @param other Второй прямоугольник
     * @return Ссылка на изменённый объект
     */
    Rectangle& operator+=(const Rectangle& other);

    /**
     * @brief Оператор пересечения с присваиванием.
     * @param other Второй прямоугольник
     * @return Ссылка на изменённый объект
     */
    Rectangle& operator-=(const Rectangle& other);

    /// Геттеры координат (inline)
    int getX1() const { return x1; };
    int getY1() const { return y1; };
    int getX2() const { return x2; };
    int getY2() const { return y2; };
};
