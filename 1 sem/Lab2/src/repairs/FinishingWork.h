#ifndef FINISHINGWORK_H
#define FINISHINGWORK_H

#include "repairs/WorkType.h"

using namespace std;

/**
 * @class FinishingWork
 * @brief Отделочные работы
 *
 * Наследуется от WorkType. Учитывает количество слоев и премиум материалы.
 */
class FinishingWork : public WorkType {
private:
    int layersCount; ///< Количество слоев
    bool premiumMaterials; ///< Премиум материалы [file:23]

public:
    /** @brief Конструктор по умолчанию */
    FinishingWork();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param baseRate Ставка
     * @param layersCount Слоев
     * @param premiumMaterials Премиум
     */
    FinishingWork(int id,
        double baseRate,
        int layersCount,
        bool premiumMaterials);

    /** @brief Возвращает количество слоев */
    int getLayersCount() const;
    /** @brief Возвращает премиум материалы */
    bool getPremiumMaterials() const;

    /** @brief Устанавливает слои */
    void setLayersCount(int value);
    /** @brief Устанавливает премиум */
    void setPremiumMaterials(bool value);

    /** @brief Расчет стоимости по площади */
    double calculateCost(double area) const override;
};

#endif
