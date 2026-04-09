#ifndef TOOL_H
#define TOOL_H

#include <string>
#include "base/Date.h"

using namespace std;

/**
 * @class Tool
 * @brief Инструменты и оборудование
 *
 * Управляет выдачей/возвратом инструментов и обслуживанием.
 */
class Tool {
private:
    int id; ///< Уникальный идентификатор
    string name; ///< Название инструмента
    string toolType; ///< Тип инструмента
    int quantity; ///< Количество
    string condition; ///< Состояние
    Date lastService; ///< Последнее обслуживание [file:32]

public:
    /** @brief Конструктор по умолчанию */
    Tool();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param toolType Тип
     * @param quantity Количество
     * @param condition Состояние
     * @param lastService Дата ТО
     */
    Tool(int id,
        const string& name,
        const string& toolType,
        int quantity,
        const string& condition,
        const Date& lastService);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает название */
    const string& getName() const;
    /** @brief Возвращает тип */
    const string& getToolType() const;
    /** @brief Возвращает количество */
    int getQuantity() const;
    /** @brief Возвращает состояние */
    const string& getCondition() const;
    /** @brief Возвращает дату ТО */
    const Date& getLastService() const;

    /** @brief Устанавливает название */
    void setName(const string& value);
    /** @brief Устанавливает тип */
    void setToolType(const string& value);
    /** @brief Устанавливает количество */
    void setQuantity(int value);
    /** @brief Устанавливает состояние */
    void setCondition(const string& value);
    /** @brief Устанавливает дату ТО */
    void setLastService(const Date& value);

    /** @brief Выдача инструмента */
    bool checkout(int amount);
    /** @brief Возврат инструмента */
    void returnBack(int amount);
    /** @brief Отметка об обслуживании */
    void markServiced(const Date& date);
};

#endif
