#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

using namespace std;

/**
 * @class Material
 * @brief Базовый класс строительных материалов
 *
 * Абстрактный класс для управления запасами материалов на складе.
 */
class Material {
protected:
    int id; ///< Уникальный идентификатор
    string name; ///< Название материала
    string unit; ///< Единица измерения
    int quantity; ///< Количество на складе
    double unitPrice; ///< Цена за единицу
    string supplier; ///< Поставщик [file:31]

public:
    /** @brief Конструктор по умолчанию */
    Material();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param unit Единица
     * @param quantity Количество
     * @param unitPrice Цена
     * @param supplier Поставщик
     */
    Material(int id,
        const string& name,
        const string& unit,
        int quantity,
        double unitPrice,
        const string& supplier);

    /** @brief Виртуальный деструктор */
    virtual ~Material() = default;

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает название */
    const string& getName() const;
    /** @brief Возвращает единицу */
    const string& getUnit() const;
    /** @brief Возвращает количество */
    int getQuantity() const;
    /** @brief Возвращает цену */
    double getUnitPrice() const;
    /** @brief Возвращает поставщика */
    const string& getSupplier() const;

    /** @brief Устанавливает название */
    void setName(const string& value);
    /** @brief Устанавливает единицу */
    void setUnit(const string& value);
    /** @brief Устанавливает количество */
    void setQuantity(int value);
    /** @brief Устанавливает цену */
    void setUnitPrice(double value);
    /** @brief Устанавливает поставщика */
    void setSupplier(const string& value);

    /** @brief Общая стоимость материала */
    virtual double getTotalCost() const;
    /** @brief Увеличение количества */
    virtual void increaseQuantity(int delta);
    /** @brief Резервирование количества */
    virtual bool reserve(int amount);
};

#endif
