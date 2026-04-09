#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include "base/Address.h"
#include "materials/Material.h"
#include "materials/Tool.h"

using namespace std;

/**
 * @class Warehouse
 * @brief Склад материалов и инструментов
 *
 * Управляет запасами и общей стоимостью товаров.
 */
class Warehouse {
private:
    int id; ///< Уникальный идентификатор
    Address* address; ///< Адрес склада
    double maxValue; ///< Максимальная стоимость запасов
    vector<Material*> materials; ///< Материалы
    vector<Tool*> tools; ///< Инструменты [file:30]

public:
    /** @brief Конструктор по умолчанию */
    Warehouse();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param address Адрес
     * @param maxValue Максимум стоимости
     */
    Warehouse(int id, Address* address, double maxValue);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает адрес */
    Address* getAddress() const;
    /** @brief Возвращает максимум стоимости */
    double getMaxValue() const;
    /** @brief Возвращает материалы */
    const vector<Material*>& getMaterials() const;
    /** @brief Возвращает инструменты */
    const vector<Tool*>& getTools() const;

    /** @brief Добавляет материал */
    void addMaterial(Material* material);
    /** @brief Добавляет инструмент */
    void addTool(Tool* tool);

    /**
     * @brief Поиск материала по названию
     * @param name Название
     * @return Указатель на материал или nullptr
     */
    Material* findMaterialByName(const string& name) const;

    /**
     * @brief Поиск инструмента по названию
     * @param name Название
     * @return Указатель на инструмент или nullptr
     */
    Tool* findToolByName(const string& name) const;

    /** @brief Общая стоимость запасов */
    double calculateTotalValue() const;
};

#endif
