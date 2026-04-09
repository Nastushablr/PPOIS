#ifndef DESIGNWORK_H
#define DESIGNWORK_H

#include "repairs/WorkType.h"

using namespace std;

/**
 * @class DesignWork
 * @brief Дизайнерские работы
 *
 * Наследуется от WorkType. Учитывает сложность и 3D-визуализацию.
 */
class DesignWork : public WorkType {
private:
    int complexityLevel; ///< Уровень сложности (1-5)
    bool includes3D; ///< Включает 3D [file:26]

public:
    /** @brief Конструктор по умолчанию */
    DesignWork();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param baseRate Ставка
     * @param complexityLevel Сложность
     * @param includes3D 3D визуализация
     */
    DesignWork(int id,
        double baseRate,
        int complexityLevel,
        bool includes3D);

    /** @brief Возвращает сложность */
    int getComplexityLevel() const;
    /** @brief Возвращает наличие 3D */
    bool getIncludes3D() const;

    /** @brief Устанавливает сложность */
    void setComplexityLevel(int value);
    /** @brief Устанавливает 3D */
    void setIncludes3D(bool value);

    /** @brief Расчет стоимости по часам */
    double calculateCost(double hours) const override;
};

#endif
