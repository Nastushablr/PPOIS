#ifndef PROJECTSTAGE_H
#define PROJECTSTAGE_H

#include <string>
#include "base/Date.h"

using namespace std;

/**
 * @class ProjectStage
 * @brief Этап ремонтного проекта
 *
 * Представляет отдельный этап работ с датами начала/окончания и процентом выполнения.
 */
class ProjectStage {
private:
    int id; ///< Уникальный идентификатор этапа
    string name; ///< Название этапа
    Date startDate; ///< Дата начала
    Date endDate; ///< Дата окончания
    int progress; ///< Процент выполнения (0-100) [file:28]

public:
    /** @brief Конструктор по умолчанию */
    ProjectStage();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название
     * @param startDate Дата начала
     * @param endDate Дата окончания
     */
    ProjectStage(int id,
        const string& name,
        const Date& startDate,
        const Date& endDate);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает название */
    const string& getName() const;
    /** @brief Возвращает дату начала */
    const Date& getStartDate() const;
    /** @brief Возвращает дату окончания */
    const Date& getEndDate() const;
    /** @brief Возвращает прогресс */
    int getProgress() const;

    /** @brief Устанавливает название */
    void setName(const string& value);
    /** @brief Устанавливает дату начала */
    void setStartDate(const Date& value);
    /** @brief Устанавливает дату окончания */
    void setEndDate(const Date& value);
    /** @brief Устанавливает прогресс */
    void setProgress(int value);

    /** @brief Проверяет завершенность этапа */
    bool isCompleted() const;
};

#endif
