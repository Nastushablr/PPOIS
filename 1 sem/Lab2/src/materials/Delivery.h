#ifndef DELIVERY_H
#define DELIVERY_H

#include <vector>
#include "base/Date.h"
#include "materials/Warehouse.h"
#include "materials/Material.h"

using namespace std;

/**
 * @class Delivery
 * @brief Перемещение материалов между складами
 *
 * Управляет логистикой материалов между складами компании.
 */
class Delivery {
private:
    int id; ///< Уникальный идентификатор
    Warehouse* fromWarehouse; ///< Склад отправления
    Warehouse* toWarehouse; ///< Склад назначения
    vector<Material*> materials; ///< Перемещаемые материалы
    Date plannedDate; ///< Плановая дата
    string status; ///< Статус ("planned", "in_transit", "completed") [file:29]

public:
    /** @brief Конструктор по умолчанию */
    Delivery();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param fromWarehouse Отправка
     * @param toWarehouse Назначение
     * @param plannedDate Дата
     */
    Delivery(int id,
        Warehouse* fromWarehouse,
        Warehouse* toWarehouse,
        const Date& plannedDate);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает склад отправки */
    Warehouse* getFromWarehouse() const;
    /** @brief Возвращает склад назначения */
    Warehouse* getToWarehouse() const;
    /** @brief Возвращает плановую дату */
    const Date& getPlannedDate() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;
    /** @brief Возвращает материалы */
    const vector<Material*>& getMaterials() const;

    /** @brief Устанавливает дату */
    void setPlannedDate(const Date& value);
    /** @brief Устанавливает статус */
    void setStatus(const string& value);

    /** @brief Добавляет материал */
    void addMaterial(Material* material);

    /** @brief Запуск доставки */
    void start();
    /** @brief Завершение доставки */
    void complete();
};

#endif
