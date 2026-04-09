#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "base/Date.h"
#include "staff/Employee.h"

using namespace std;

/**
 * @class Vehicle
 * @brief Класс для представления транспортных средств компании
 *
 * Хранит информацию о техническом состоянии, водителе и расходует топливо.
 * Поддерживает расчет расхода топлива и учет пробега.
 */
class Vehicle {
private:
    int id; ///< Уникальный идентификатор
    string plateNumber; ///< Номерной знак
    string model; ///< Модель автомобиля
    double fuelConsumptionPer100km; ///< Расход топлива на 100 км
    Employee* driver; ///< Назначенный водитель
    Date lastServiceDate; ///< Дата последнего ТО
    double mileage; ///< Пробег [file:19]

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Vehicle();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param plateNumber Номерной знак
     * @param model Модель
     * @param fuelConsumptionPer100km Расход топлива л/100км
     * @param driver Водитель
     * @param lastServiceDate Дата ТО
     * @param mileage Пробег
     */
    Vehicle(int id,
        const string& plateNumber,
        const string& model,
        double fuelConsumptionPer100km,
        Employee* driver,
        const Date& lastServiceDate,
        double mileage);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает номерной знак */
    const string& getPlateNumber() const;
    /** @brief Возвращает модель */
    const string& getModel() const;
    /** @brief Возвращает расход топлива */
    double getFuelConsumptionPer100km() const;
    /** @brief Возвращает водителя */
    Employee* getDriver() const;
    /** @brief Возвращает дату ТО */
    const Date& getLastServiceDate() const;
    /** @brief Возвращает пробег */
    double getMileage() const;

    /** @brief Устанавливает номерной знак */
    void setPlateNumber(const string& value);
    /** @brief Устанавливает модель */
    void setModel(const string& value);
    /** @brief Устанавливает расход топлива */
    void setFuelConsumptionPer100km(double value);
    /** @brief Устанавливает водителя */
    void setDriver(Employee* value);
    /** @brief Устанавливает дату ТО */
    void setLastServiceDate(const Date& value);
    /** @brief Устанавливает пробег */
    void setMileage(double value);

    /**
     * @brief Расчет расхода топлива на расстояние
     * @param km Расстояние в км
     * @return Необходимое количество топлива в литрах
     */
    double estimateFuelForDistance(double km) const;

    /** @brief Добавляет поездку к пробегу */
    void addTrip(double km);
};

#endif
