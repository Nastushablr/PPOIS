#ifndef MASONRYWORK_H
#define MASONRYWORK_H

#include "repairs/WorkType.h"

using namespace std;

/**
 * @class MasonryWork
 * @brief Каменные работы
 *
 * Наследуется от WorkType. Учитывает толщину стен и необходимость лесов.
 */
class MasonryWork : public WorkType {
private:
    double wallThickness; ///< Толщина стен (см)
    bool requiresScaffolding; ///< Требуются леса [file:25]

public:
    /** @brief Конструктор по умолчанию */
    MasonryWork();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param baseRate Ставка
     * @param wallThickness Толщина
     * @param requiresScaffolding Леса
     */
    MasonryWork(int id,
        double baseRate,
        double wallThickness,
        bool requiresScaffolding);

    /** @brief Возвращает толщину стен */
    double getWallThickness() const;
    /** @brief Возвращает необходимость лесов */
    bool getRequiresScaffolding() const;

    /** @brief Устанавливает толщину */
    void setWallThickness(double value);
    /** @brief Устанавливает леса */
    void setRequiresScaffolding(bool value);

    /** @brief Расчет стоимости по площади */
    double calculateCost(double area) const override;
};

#endif
