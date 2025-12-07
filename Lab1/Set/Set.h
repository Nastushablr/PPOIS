#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/// Класс множества с поддержкой вложенных подмножеств.
/**
 * Элементы: строки или указатели на подмножества.
 * Формат сериализации: "{a,b,{c,d}}".
 * Поддерживает операции ∪(+), ∩(*), \(-), степень множества.
 */
class Set {
private:
    /**
     * @brief Внутренняя структура элемента множества.
     */
    struct Element {
        bool isSet;     ///< true=подмножество, false=строка
        string value;   ///< значение строки
        Set* subset;    ///< указатель на подмножество
    };
    vector<Element> data; ///< Контейнер элементов

public:
    /**
     * @brief Проверяет наличие строкового элемента.
     * @param v Искомая строка
     * @return true если элемент присутствует
     */
    bool containsElement(const string& v) const;

    /**
     * @brief Конструктор по умолчанию. Создаёт пустое множество.
     */
    Set();

    /**
     * @brief Конструктор копирования (глубокая копия).
     * @param other Исходное множество
     */
    Set(const Set& other);

    /**
     * @brief Оператор присваивания (глубокая копия).
     * @param other Исходное множество
     * @return Ссылка на изменённый объект
     */
    Set& operator=(const Set& other);

    /**
     * @brief Деструктор. Освобождает динамическую память подмножеств.
     */
    ~Set();

    /**
     * @brief Конструктор из строки формата "{a,b,{c,d}}".
     * @param text Строка представления множества
     */
    explicit Set(const string& text);

    /**
     * @brief Статический метод валидации строки множества.
     * @param text Проверяемая строка
     * @return true если формат корректен (сбалансированы скобки {})
     */
    static bool IsValidString(const string& text);

    /**
     * @brief Проверяет пустоту множества.
     * @return true если множество пустое
     */
    bool isEmpty() const;

    /**
     * @brief Добавляет строковый элемент (дубликаты игнорируются).
     * @param value Добавляемая строка
     */
    void addElement(const string& value);

    /**
     * @brief Добавляет подмножество (глубокая копия).
     * @param s Добавляемое множество
     */
    void addSet(const Set& s);

    /**
     * @brief Удаляет строковый элемент.
     * @param value Удаляемая строка
     * @return true если элемент был найден и удалён
     */
    bool removeElement(const string& value);

    /**
     * @brief Возвращает количество элементов (строки + подмножества).
     * @return Размер множества
     */
    int size() const;

    /**
     * @brief Оператор проверки наличия элемента (синоним containsElement).
     * @param value Искомая строка
     * @return true если элемент присутствует
     */
    bool operator[](const string& value) const;

    /**
     * @brief Объединение множеств (∪).
     * @param other Второе множество
     * @return Новое множество-объединение
     */
    Set operator+(const Set& other) const;

    /**
     * @brief Объединение с присваиванием (∪=).
     * @param other Второе множество
     * @return Ссылка на изменённый объект
     */
    Set& operator+=(const Set& other);

    /**
     * @brief Пересечение множеств (∩) - общие строковые элементы.
     * @param other Второе множество
     * @return Новое множество-пересечение
     */
    Set operator*(const Set& other) const;

    /**
     * @brief Пересечение с присваиванием (∩=).
     * @param other Второе множество
     * @return Ссылка на изменённый объект
     */
    Set& operator*=(const Set& other);

    /**
     * @brief Разность множеств (\) - элементы только в первом.
     * @param other Вычитаемое множество
     * @return Новое множество-разность
     */
    Set operator-(const Set& other) const;

    /**
     * @brief Разность с присваиванием (\=).
     * @param other Вычитаемое множество
     * @return Ссылка на изменённый объект
     */
    Set& operator-=(const Set& other);

    /**
     * @brief Степень множества (все возможные подмножества строковых элементов).
     * Для множества размера n возвращает 2^n подмножеств.
     * @return Множество всех подмножеств
     */
    Set powerSet() const;

    /**
     * @brief Оператор вывода в поток. Формат: "{a,b,{c,d}}".
     */
    friend ostream& operator<<(ostream& out, const Set& s);

    /**
     * @brief Оператор ввода из потока с валидацией формата.
     */
    friend istream& operator>>(istream& in, Set& s);
};
