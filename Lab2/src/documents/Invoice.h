#ifndef INVOICE_H
#define INVOICE_H

#include <vector>
#include "documents/Document.h"
#include "clients/Client.h"

using namespace std;

/**
 * @class Invoice
 * @brief Счет-фактура клиенту
 *
 * Содержит НДС, сроки оплаты и позиции счета.
 */
class Invoice : public Document {
private:
    Client* client; ///< Клиент
    double amount; ///< Сумма без НДС
    double taxRate; ///< Ставка НДС
    Date dueDate; ///< Дата оплаты
    string paymentStatus; ///< Статус оплаты
    vector<string> items; ///< Позиции счета [file:38]

public:
    /** @brief Конструктор по умолчанию */
    Invoice();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param client Клиент
     * @param amount Сумма
     * @param taxRate НДС
     * @param dueDate Срок оплаты
     */
    Invoice(int id,
        const Date& created,
        Employee* author,
        Client* client,
        double amount,
        double taxRate,
        const Date& dueDate);

    /** @brief Возвращает клиента */
    Client* getClient() const;
    /** @brief Возвращает сумму */
    double getAmount() const;
    /** @brief Возвращает НДС */
    double getTaxRate() const;
    /** @brief Возвращает срок оплаты */
    Date getDueDate() const;
    /** @brief Возвращает статус оплаты */
    const string& getPaymentStatus() const;
    /** @brief Возвращает позиции */
    const vector<string>& getItems() const;

    /** @brief Устанавливает сумму */
    void setAmount(double value);
    /** @brief Устанавливает НДС */
    void setTaxRate(double value);
    /** @brief Устанавливает срок оплаты */
    void setDueDate(const Date& value);

    /** @brief Добавляет позицию */
    void addItem(const string& line);

    /** @brief Сумма с НДС */
    double getTotalWithTax() const;
    /** @brief Отметка об оплате */
    void markPaid();

    /** @brief Проверяет просрочку */
    bool isOverdue(const Date& today) const;

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
