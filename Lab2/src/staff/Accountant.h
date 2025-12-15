#ifndef ACCOUNTANT_H
#define ACCOUNTANT_H

#include <string>
#include "staff/Employee.h"

using namespace std;

/**
 * @class Accountant
 * @brief Класс для бухгалтеров
 *
 * Отслеживает квалификацию и количество закрытых отчетов.
 */
class Accountant : public Employee {
private:
    string qualificationLevel; ///< Уровень квалификации
    int closedReports; ///< Закрытых отчетов [file:12]

public:
    /** @brief Конструктор по умолчанию */
    Accountant();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     * @param qualificationLevel Квалификация
     */
    Accountant(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        const string& qualificationLevel);

    /** @brief Возвращает квалификацию */
    const string& getQualificationLevel() const;
    /** @brief Возвращает количество отчетов */
    int getClosedReports() const;

    /** @brief Устанавливает квалификацию */
    void setQualificationLevel(const string& value);

    /** @brief Создание счета */
    void createInvoice(double amount);
    /** @brief Закрытие месячного отчета */
    void closeMonthlyReport();

    /** @brief Расчет зарплаты */
    double calculateMonthlySalary() const override;
    /** @brief Возвращает роль "Accountant" */
    string getRole() const override;
};

#endif
