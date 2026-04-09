#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include "documents/Document.h"
#include "clients/Client.h"
#include "repairs/RepairProject.h"

using namespace std;

/**
 * @class Contract
 * @brief Договор с клиентом на ремонтные работы
 *
 * Наследуется от Document. Содержит сроки, сумму и условия договора.
 */
class Contract : public Document {
private:
    Client* client; ///< Клиент
    RepairProject* project; ///< Связанный проект
    Date startDate; ///< Дата начала работ
    Date endDate; ///< Дата окончания работ
    double amount; ///< Сумма договора
    string termsText; ///< Условия договора [file:35]

public:
    /** @brief Конструктор по умолчанию */
    Contract();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param client Клиент
     * @param startDate Начало работ
     * @param endDate Окончание работ
     * @param amount Сумма
     */
    Contract(int id,
        const Date& created,
        Employee* author,
        Client* client,
        const Date& startDate,
        const Date& endDate,
        double amount);

    /** @brief Возвращает клиента */
    Client* getClient() const;
    /** @brief Возвращает проект */
    RepairProject* getProject() const;
    /** @brief Возвращает дату начала */
    const Date& getStartDate() const;
    /** @brief Возвращает дату окончания */
    const Date& getEndDate() const;
    /** @brief Возвращает сумму */
    double getAmount() const;
    /** @brief Возвращает условия */
    const string& getTermsText() const;

    /** @brief Устанавливает проект */
    void setProject(RepairProject* value);
    /** @brief Устанавливает дату начала */
    void setStartDate(const Date& value);
    /** @brief Устанавливает дату окончания */
    void setEndDate(const Date& value);
    /** @brief Устанавливает сумму */
    void setAmount(double value);
    /** @brief Устанавливает условия */
    void setTermsText(const string& value);

    /** @brief Подписание договора */
    void sign();
    /** @brief Расторжение договора */
    void terminate();

    /** @brief Проверяет активность на дату */
    bool isActiveOn(const Date& date) const;

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
