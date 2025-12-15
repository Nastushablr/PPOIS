#ifndef FINANCIALREPORT_H
#define FINANCIALREPORT_H

#include <vector>
#include "documents/Document.h"
#include "documents/Invoice.h"
#include "documents/Payment.h"

using namespace std;

/**
 * @class FinancialReport
 * @brief Финансовый отчет за период
 *
 * Агрегирует счета и платежи для анализа дебиторки.
 */
class FinancialReport : public Document {
private:
    string periodLabel; ///< Период отчета
    vector<Invoice*> invoices; ///< Счета
    vector<Payment*> payments; ///< Платежи
    double totalInvoiced; ///< Выставлено всего
    double totalPaid; ///< Оплачено всего
    double totalOutstanding; ///< Долг [file:37]

public:
    /** @brief Конструктор по умолчанию */
    FinancialReport();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param periodLabel Период
     */
    FinancialReport(int id,
        const Date& created,
        Employee* author,
        const string& periodLabel);

    /** @brief Возвращает период */
    const string& getPeriodLabel() const;
    /** @brief Возвращает счета */
    const vector<Invoice*>& getInvoices() const;
    /** @brief Возвращает платежи */
    const vector<Payment*>& getPayments() const;
    /** @brief Возвращает выставлено */
    double getTotalInvoiced() const;
    /** @brief Возвращает оплачено */
    double getTotalPaid() const;
    /** @brief Возвращает долг */
    double getTotalOutstanding() const;

    /** @brief Добавляет счет */
    void addInvoice(Invoice* invoice);
    /** @brief Добавляет платеж */
    void addPayment(Payment* payment);

    /** @brief Очищает данные */
    void clearData();
    /** @brief Пересчитывает итоги */
    void recalculateTotals();

    /** @brief Процент оплаты */
    double getPaidPercent() const;

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
