#ifndef REPAIRSPECIALIST_H
#define REPAIRSPECIALIST_H

#include <string>
#include "staff/Employee.h"

using namespace std;

/**
 * @class RepairSpecialist
 * @brief Базовый класс для ремонтных специалистов
 *
 * Наследуется от Employee. Отслеживает специализацию, уровень навыков
 * и выполненные задачи. Абстрактный класс.
 */
class RepairSpecialist : public Employee {
protected:
    string specialization; ///< Специализация
    int completedTasks; ///< Выполненных задач
    int skillLevel; ///< Уровень навыков [file:10]

public:
    /** @brief Конструктор по умолчанию */
    RepairSpecialist();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     * @param specialization Специализация
     */
    RepairSpecialist(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        const string& specialization);

    /** @brief Возвращает количество задач */
    int getCompletedTasks() const;
    /** @brief Возвращает уровень навыков */
    int getSkillLevel() const;
    /** @brief Возвращает специализацию */
    const string& getSpecialization() const;

    /** @brief Повышение уровня навыков */
    void increaseSkill();
    /** @brief Регистрация выполненной задачи */
    void registerCompletedTask();

    /** @brief Расчет зарплаты */
    double calculateMonthlySalary() const override;
    /** @brief Абстрактный метод роли */
    virtual string getRole() const override = 0;
};

#endif
