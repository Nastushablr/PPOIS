#ifndef PRICELIST_H
#define PRICELIST_H

#include <string>
#include <map>
#include "repairs/WorkType.h"

using namespace std;

/**
 * @class PriceList
 * @brief Класс для управления прайс-листом услуг
 *
 * Хранит базовые ставки работ и наценку на материалы.
 */
class PriceList {
private:
    string name; ///< Название прайс-листа
    map<int, double> workBaseRates; ///< Базовые ставки работ по ID типа
    double materialMarkupPercent; ///< Наценка на материалы в % [file:20]

public:
    /** @brief Конструктор по умолчанию */
    PriceList();

    /**
     * @brief Конструктор с параметрами
     * @param name Название
     * @param materialMarkupPercent Наценка на материалы
     */
    PriceList(const string& name, double materialMarkupPercent);

    /** @brief Возвращает название */
    const string& getName() const;
    /** @brief Возвращает наценку на материалы */
    double getMaterialMarkupPercent() const;

    /** @brief Устанавливает название */
    void setName(const string& value);
    /** @brief Устанавливает наценку */
    void setMaterialMarkupPercent(double value);

    /**
     * @brief Устанавливает ставку для типа работ
     * @param workTypeId ID типа работ
     * @param rate Ставка
     */
    void setWorkRate(int workTypeId, double rate);

    /**
     * @brief Проверяет наличие ставки
     * @param workTypeId ID типа работ
     * @return true если ставка существует
     */
    bool hasWorkRate(int workTypeId) const;

    /**
     * @brief Получает ставку для типа работ
     * @param workTypeId ID типа работ
     * @return Ставка или 0 если не найдена
     */
    double getWorkRate(int workTypeId) const;

    /**
     * @brief Расчет стоимости работы
     * @param workType Тип работы
     * @param amount Объем/количество
     * @return Общая стоимость работы
     */
    double calculateWorkCost(const WorkType* workType, double amount) const;

    /**
     * @brief Применение наценки к материалам
     * @param materialCost Стоимость материалов
     * @return Стоимость с наценкой
     */
    double applyMaterialMarkup(double materialCost) const;
};

#endif
