#ifndef HRSPECIALIST_H
#define HRSPECIALIST_H

#include <string>
#include "staff/Employee.h"

using namespace std;

/**
 * @class HRSpecialist
 * @brief Класс для специалистов по кадрам
 *
 * Отслеживает количество проведенных собеседований и принятых сотрудников.
 */
class HRSpecialist : public Employee {
private:
    int hiredEmployees; ///< Принятых сотрудников
    int interviewsCount; ///< Проведенных собеседований [file:17]

public:
    /** @brief Конструктор по умолчанию */
    HRSpecialist();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     */
    HRSpecialist(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary);

    /** @brief Возвращает количество принятых */
    int getHiredEmployees() const;
    /** @brief Возвращает количество собеседований */
    int getInterviewsCount() const;

    /** @brief Регистрация собеседования */
    void registerInterview();
    /** @brief Прием нового сотрудника */
    void hireNewEmployee();

    /** @brief Расчет зарплаты */
    double calculateMonthlySalary() const override;
    /** @brief Возвращает роль "HRSpecialist" */
    string getRole() const override;
};

#endif
