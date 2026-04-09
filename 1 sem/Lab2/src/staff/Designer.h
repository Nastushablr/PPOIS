#ifndef DESIGNER_H
#define DESIGNER_H

#include <string>
#include "staff/RepairSpecialist.h"

using namespace std;

/**
 * @class Designer
 * @brief Класс для дизайнеров
 *
 * Наследуется от RepairSpecialist. Специализируется на основном стиле и создании проектов.
 */
class Designer : public RepairSpecialist {
private:
    string mainStyle; ///< Основной стиль
    int createdDesigns; ///< Созданных проектов [file:14]

public:
    /** @brief Конструктор по умолчанию */
    Designer();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Личные данные
     * @param hireDate Дата приема
     * @param baseSalary Оклад
     * @param mainStyle Основной стиль
     */
    Designer(int id,
        Person* person,
        const Date& hireDate,
        double baseSalary,
        const string& mainStyle);

    /** @brief Возвращает основной стиль */
    const string& getMainStyle() const;
    /** @brief Возвращает количество проектов */
    int getCreatedDesigns() const;

    /** @brief Устанавливает основной стиль */
    void setMainStyle(const string& value);

    /** @brief Создание проекта */
    void createDesign();

    /** @brief Возвращает роль "Designer" */
    string getRole() const override;
};

#endif
