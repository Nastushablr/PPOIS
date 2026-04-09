#ifndef ELECTRICIAN_H
#define ELECTRICIAN_H

#include <string>
#include "staff/RepairSpecialist.h"

using namespace std;

/**
 * @class Electrician
 * @brief Класс для электриков
 *
 * Наследуется от RepairSpecialist. Работает с высоковольтным оборудованием.
 */
class Electrician : public RepairSpecialist {
private:
    bool hasHighVoltagePermit; ///< Допуск к высокому напряжению
    int safetyChecksDone; ///< Техосмотров проведено [file:11]

public:
    /** @brief Конструктор по умолчанию */
    Electrician();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     * @param highVoltagePermit Допуск к ВН
     */
    Electrician(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        bool highVoltagePermit);

    /** @brief Возвращает допуск к ВН */
    bool getHasHighVoltagePermit() const;
    /** @brief Возвращает количество техосмотров */
    int getSafetyChecksDone() const;

    /** @brief Устанавливает допуск к ВН */
    void setHasHighVoltagePermit(bool value);

    /** @brief Выполнение ремонта */
    void performRepair();
    /** @brief Техосмотр */
    void performSafetyCheck();

    /** @brief Возвращает роль "Electrician" */
    string getRole() const override;
};

#endif
