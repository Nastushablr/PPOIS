#ifndef PAYMENT_H
#define PAYMENT_H

#include "documents/Document.h"
#include "documents/Invoice.h"

using namespace std;

/**
 * @class Payment
 * @brief Платеж от клиента
 *
 * Связан со счетом-фактурой и методом оплаты.
 */
class Payment : public Document {
private:
    Invoice* invoice; ///< Связанный счет
    double amount; ///< Сумма платежа
    Date paymentDate; ///< Дата платежа
    string method; ///< Метод оплаты
    string transactionId; ///< ID транзакции
    bool refunded; ///< Возвращен [file:39]

public:
    /** @brief Конструктор по умолчанию */
    Payment();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param invoice Счет
     * @param amount Сумма
     * @param paymentDate Дата
     * @param method Метод
     */
    Payment(int id,
        const Date& created,
        Employee* author,
        Invoice* invoice,
        double amount,
        const Date& paymentDate,
        const string& method);

    /** @brief Возвращает счет */
    Invoice* getInvoice() const;
    /** @brief Возвращает сумму */
    double getAmount() const;
    /** @brief Возвращает дату платежа */
    const Date& getPaymentDate() const;
    /** @brief Возвращает метод */
    const string& getMethod() const;
    /** @brief Возвращает ID транзакции */
    const string& getTransactionId() const;
    /** @brief Проверяет возврат */
    bool isRefunded() const;

    /** @brief Устанавливает дату платежа */
    void setPaymentDate(const Date& value);
    /** @brief Устанавливает метод */
    void setMethod(const string& value);
    /** @brief Устанавливает ID транзакции */
    void setTransactionId(const string& value);

    /** @brief Отметка обработки */
    void markProcessed();
    /** @brief Отметка ошибки */
    void markFailed();
    /** @brief Отметка возврата */
    void markRefunded();

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
