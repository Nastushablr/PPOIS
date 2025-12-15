#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "staff/Employee.h"

using namespace std;

/**
 * @class Manager
 * @brief Класс для представления руководителей подразделений
 *
 * Наследуется от Employee. Отслеживает размер команды, рейтинг эффективности
 * и управляет задачами подразделения.
 */
class Manager : public Employee {
private:
    string department; ///< Отдел
    int teamSize; ///< Размер команды
    double performanceRating; ///< Рейтинг эффективности [file:16]

public:
    /** @brief Конструктор по умолчанию */
    Manager();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     * @param department Отдел
     */
    Manager(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        const string& department);

    /** @brief Возвращает отдел */
    const string& getDepartment() const;
    /** @brief Возвращает размер команды */
    int getTeamSize() const;
    /** @brief Возвращает рейтинг эффективности */
    double getPerformanceRating() const;

    /** @brief Устанавливает отдел */
    void setDepartment(const string& value);
    /** @brief Устанавливает размер команды */
    void setTeamSize(int value);
    /** @brief Устанавливает рейтинг эффективности */
    void setPerformanceRating(double value);

    /** @brief Назначение задачи */
    void assignTask(int taskId);
    /** @brief Проведение собрания */
    void conductMeeting();
    /** @brief Добавление члена команды */
    void addTeamMember();

    /** @brief Расчет зарплаты с учетом команды */
    double calculateMonthlySalary() const override;
    /** @brief Возвращает роль "Manager" */
    string getRole() const override;
};

#endif
