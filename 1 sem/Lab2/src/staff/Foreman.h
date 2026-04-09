#ifndef FOREMAN_H
#define FOREMAN_H

#include "staff/RepairSpecialist.h"

using namespace std;

/**
 * @class Foreman
 * @brief Класс для прорабов
 *
 * Наследуется от RepairSpecialist. Управляет бригадой и планирует работы.
 */
class Foreman : public RepairSpecialist {
private:
    int teamSize; ///< Размер бригады
    int finishedProjects; ///< Завершенных проектов [file:13]

public:
    /** @brief Конструктор по умолчанию */
    Foreman();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     */
    Foreman(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary);

    /** @brief Возвращает размер бригады */
    int getTeamSize() const;
    /** @brief Возвращает количество проектов */
    int getFinishedProjects() const;

    /** @brief Устанавливает размер бригады */
    void setTeamSize(int value);

    /** @brief Регистрация завершенного проекта */
    void registerFinishedProject();
    /** @brief Планирование графика */
    void planSchedule();

    /** @brief Возвращает роль "Foreman" */
    string getRole() const override;
};

#endif
