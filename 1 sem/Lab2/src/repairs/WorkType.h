#ifndef WORKTYPE_H
#define WORKTYPE_H

#include <string>

using namespace std;

/**
 * @class WorkType
 * @brief Базовый класс типов ремонтных работ
 *
 * Абстрактный класс для расчета стоимости работ.
 */
class WorkType {
protected:
    int id; ///< Уникальный идентификатор
    string name; ///< Название типа работ
    double baseRate; ///< Базовая ставка
    string unit; ///< Единица измерения
    string description; ///< Описание [file:22]

public:
    /** @brief Конструктор по умолчанию */
    WorkType();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param baseRate Базовая ставка
     * @param unit Единица
     * @param description Описание
     */
    WorkType(int id,
        const string& name,
        double baseRate,
        const string& unit,
        const string& description);

    /** @brief Виртуальный деструктор */
    virtual ~WorkType() = default;

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает название */
    const string& getName() const;
    /** @brief Возвращает ставку */
    double getBaseRate() const;
    /** @brief Возвращает единицу */
    const string& getUnit() const;
    /** @brief Возвращает описание */
    const string& getDescription() const;

    /** @brief Устанавливает название */
    void setName(const string& value);
    /** @brief Устанавливает ставку */
    void setBaseRate(double value);
    /** @brief Устанавливает единицу */
    void setUnit(const string& value);
    /** @brief Устанавливает описание */
    void setDescription(const string& value);

    /** @brief Абстрактный расчет стоимости */
    virtual double calculateCost(double amount) const = 0;
};

#endif
