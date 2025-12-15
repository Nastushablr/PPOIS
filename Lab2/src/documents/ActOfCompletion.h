#ifndef ACTOFCOMPLETION_H
#define ACTOFCOMPLETION_H

#include "documents/Document.h"
#include "repairs/RepairProject.h"

using namespace std;

/**
 * @class ActOfCompletion
 * @brief Акт выполненных работ
 *
 * Подписывается клиентом при приемке работ.
 */
class ActOfCompletion : public Document {
private:
    RepairProject* project; ///< Связанный проект
    Date completionDate; ///< Дата завершения
    string customerComment; ///< Комментарий клиента
    int qualityScore; ///< Оценка качества [file:41]

public:
    /** @brief Конструктор по умолчанию */
    ActOfCompletion();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param project Проект
     * @param completionDate Дата завершения
     */
    ActOfCompletion(int id,
        const Date& created,
        Employee* author,
        RepairProject* project,
        const Date& completionDate);

    /** @brief Возвращает проект */
    RepairProject* getProject() const;
    /** @brief Возвращает дату завершения */
    const Date& getCompletionDate() const;
    /** @brief Возвращает комментарий */
    const string& getCustomerComment() const;
    /** @brief Возвращает оценку */
    int getQualityScore() const;

    /** @brief Устанавливает дату завершения */
    void setCompletionDate(const Date& value);
    /** @brief Устанавливает комментарий */
    void setCustomerComment(const string& value);
    /** @brief Устанавливает оценку */
    void setQualityScore(int value);

    /** @brief Подпись клиента */
    void signByCustomer();
    /** @brief Проверяет подпись */
    bool isSigned() const;

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
