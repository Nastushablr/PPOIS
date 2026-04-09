#ifndef FINISHINGMATERIAL_H
#define FINISHINGMATERIAL_H

#include <string>
#include "materials/Material.h"

using namespace std;

/**
 * @class FinishingMaterial
 * @brief Отделочные материалы (краска, обои и т.д.)
 *
 * Наследуется от Material. Хранит цвет, тип отделки и расход.
 */
class FinishingMaterial : public Material {
private:
    string color; ///< Цвет
    string finishType; ///< Тип отделки
    double coverage; ///< Расход м²/ед [file:34]

public:
    /** @brief Конструктор по умолчанию */
    FinishingMaterial();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param unit Единица
     * @param quantity Количество
     * @param unitPrice Цена
     * @param supplier Поставщик
     * @param color Цвет
     * @param finishType Тип отделки
     * @param coverage Расход
     */
    FinishingMaterial(int id,
        const string& name,
        const string& unit,
        int quantity,
        double unitPrice,
        const string& supplier,
        const string& color,
        const string& finishType,
        double coverage);

    /** @brief Возвращает цвет */
    const string& getColor() const;
    /** @brief Возвращает тип отделки */
    const string& getFinishType() const;
    /** @brief Возвращает расход */
    double getCoverage() const;

    /** @brief Устанавливает цвет */
    void setColor(const string& value);
    /** @brief Устанавливает тип отделки */
    void setFinishType(const string& value);
    /** @brief Устанавливает расход */
    void setCoverage(double value);

    /** @brief Площадь покрытия материала */
    double getCoverableArea() const;
};

#endif
