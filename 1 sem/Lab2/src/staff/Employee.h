#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "base/Person.h"
#include "base/Date.h"

using namespace std;

/**
 * @class Employee
 * @brief Базовый класс для представления сотрудников компании
 *
 * Содержит основную информацию о сотруднике: личные данные, дата приема,
 * оклад, должность и статус. Предоставляет базовые операции управления кадрами.
 */
class Employee {
protected:
    int id; ///< Уникальный идентификатор сотрудника
    Person* person; ///< Личные данные сотрудника
    Date hireDate; ///< Дата приема на работу
    double baseSalary; ///< Базовый оклад
    string position; ///< Должность
    string status; ///< Статус сотрудника [file:15]

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Employee();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Базовый оклад
     * @param position Должность
     */
    Employee(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        const string& position);

    /** @brief Виртуальный деструктор */
    virtual ~Employee() = default;

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает личные данные */
    Person* getPerson() const;
    /** @brief Возвращает дату приема */
    const Date& getHireDate() const;
    /** @brief Возвращает базовый оклад */
    double getBaseSalary() const;
    /** @brief Возвращает должность */
    const string& getPosition() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;

    /** @brief Устанавливает личные данные */
    void setPerson(Person* value);
    /** @brief Устанавливает дату приема */
    void setHireDate(const Date& value);
    /** @brief Устанавливает базовый оклад */
    void setBaseSalary(double value);
    /** @brief Устанавливает должность */
    void setPosition(const string& value);
    /** @brief Устанавливает статус */
    void setStatus(const string& value);

    /** @brief Прием на работу */
    void hire();
    /** @brief Увольнение */
    void dismiss();
    /** @brief Отправка в отпуск */
    void sendToLeave();

    /**
     * @brief Вычисляет стаж работы
     * @param today Текущая дата
     * @return Количество полных лет стажа
     */
    int getExperienceYears(const Date& today) const;

    /**
     * @brief Расчет месячной зарплаты (виртуальный)
     * @return Месячная зарплата с учетом надбавок
     */
    virtual double calculateMonthlySalary() const;

    /** @brief Возвращает роль сотрудника (абстрактный метод) */
    virtual string getRole() const = 0;
};

#endif
