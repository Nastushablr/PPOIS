#ifndef REPAIROBJECT_H
#define REPAIROBJECT_H

#include <string>
#include "base/Address.h"
#include "clients/Client.h"

using namespace std;

/**
 * @class RepairObject
 * @brief Объект ремонта (квартира, дом, офис и т.д.)
 *
 * Хранит характеристики объекта и владельца.
 */
class RepairObject {
private:
    int id; ///< Уникальный идентификатор
    Address* address; ///< Адрес объекта
    Client* owner; ///< Владелец
    string objectType; ///< Тип ("квартира", "дом", "офис")
    double area; ///< Площадь м²
    int buildYear; ///< Год постройки [file:21]

public:
    /** @brief Конструктор по умолчанию */
    RepairObject();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param address Адрес
     * @param owner Владелец
     * @param objectType Тип объекта
     * @param area Площадь
     * @param buildYear Год постройки
     */
    RepairObject(int id,
        Address* address,
        Client* owner,
        const string& objectType,
        double area,
        int buildYear);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает адрес */
    Address* getAddress() const;
    /** @brief Возвращает владельца */
    Client* getOwner() const;
    /** @brief Возвращает тип */
    const string& getObjectType() const;
    /** @brief Возвращает площадь */
    double getArea() const;
    /** @brief Возвращает год постройки */
    int getBuildYear() const;

    /** @brief Устанавливает адрес */
    void setAddress(Address* value);
    /** @brief Устанавливает владельца */
    void setOwner(Client* value);
    /** @brief Устанавливает тип */
    void setObjectType(const string& value);
    /** @brief Устанавливает площадь */
    void setArea(double value);
    /** @brief Устанавливает год постройки */
    void setBuildYear(int value);

    /** @brief Проверяет старый ли дом (< 2000 г.) */
    bool isOldBuilding() const;
};

#endif
