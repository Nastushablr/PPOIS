#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

/**
 * @class Date
 * @brief Класс для представления и манипуляции датами в формате день.месяц.год
 *
 * Поддерживает валидацию дат, арифметику дат, сравнение и форматированный вывод.
 * Автоматически корректирует невалидные даты на значение по умолчанию (01.01.2000).
 */
class Date {
private:
    int day; ///< День месяца (1-31)
    int month; ///< Месяц (1-12)
    int year; ///< Год (>=1)

    /**
     * @brief Проверяет валидность текущей даты
     * @return true если дата корректная (учитывает високосные годы)
     */
    bool validateDateRange() const;

    /**
     * @brief Проверяет високосный ли год
     * @param y Год для проверки
     * @return true для високосного года
     */
    bool isLeap(int y) const;

    /**
     * @brief Возвращает количество дней в указанном месяце
     * @param m Номер месяца
     * @param y Год
     * @return Количество дней (29 для февраля в високосный год)
     */
    int daysInMonth(int m, int y) const;

public:
    /**
     * @brief Конструктор по умолчанию
     * Инициализирует дату 01.01.2000
     */
    Date();

    /**
     * @brief Конструктор с параметрами
     * @param d День
     * @param m Месяц
     * @param y Год
     * Невалидные даты заменяются на 01.01.2000
     */
    Date(int d, int m, int y);

    /** @brief Возвращает день */
    int getDay() const;

    /** @brief Возвращает месяц */
    int getMonth() const;

    /** @brief Возвращает год */
    int getYear() const;

    /**
     * @brief Устанавливает дату
     * @param d День
     * @param m Месяц
     * @param y Год
     * Невалидные значения сбрасываются на 01.01.2000 [file:3][file:4]
     */
    void setDate(int d, int m, int y);

    /** @brief Проверяет валидность текущей даты */
    bool isValid() const;

    /**
     * @brief Вычисляет количество дней между датами
     * @param other Целевая дата
     * @return Положительное число дней если this < other, отрицательное если this > other, 0 если равны
     */
    int daysUntil(const Date& other) const;

    /**
     * @brief Добавляет дни к текущей дате (только положительные значения)
     * @param days Количество дней для добавления
     */
    void addDays(int days);

    /**
     * @brief Форматированный вывод даты
     * @return Строка в формате DD.MM.YYYY (с ведущими нулями)
     */
    string toString() const;

    /** @brief Оператор меньше */
    bool operator<(const Date& other) const;
    /** @brief Оператор больше */
    bool operator>(const Date& other) const;
    /** @brief Оператор равенства */
    bool operator==(const Date& other) const;
};

#endif
