#ifndef BUILDINGMATERIAL_H
#define BUILDINGMATERIAL_H

#include "materials/Material.h"

using namespace std;

/**
 * @class BuildingMaterial
 * @brief Строительные материалы (кирпич, бетон и т.д.)
 *
 * Наследуется от Material. Хранит характеристики прочности и плотности.
 */
class BuildingMaterial : public Material {
private:
    string strengthClass; ///< Класс прочности
    bool forOutdoorUse; ///< Для наружных работ
    double density; ///< Плотность кг/м³ [file:33]

public:
    /** @brief Конструктор по умолчанию */
    BuildingMaterial();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param unit Единица
     * @param quantity Количество
     * @param unitPrice Цена
     * @param supplier Поставщик
     * @param strengthClass Прочность
     * @param forOutdoorUse Наружные работы
     * @param density Плотность
     */
    BuildingMaterial(int id,
        const string& name,
        const string& unit,
        int quantity,
        double unitPrice,
        const string& supplier,
        const string& strengthClass,
        bool forOutdoorUse,
        double density);

    /** @brief Возвращает класс прочности */
    const string& getStrengthClass() const;
    /** @brief Проверяет наружные работы */
    bool isForOutdoorUse() const;
    /** @brief Возвращает плотность */
    double getDensity() const;

    /** @brief Устанавливает прочность */
    void setStrengthClass(const string& value);
    /** @brief Устанавливает наружные работы */
    void setForOutdoorUse(bool value);
    /** @brief Устанавливает плотность */
    void setDensity(double value);

    /** @brief Переопределение общей стоимости */
    double getTotalCost() const override;
};

#endif
