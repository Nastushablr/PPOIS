#ifndef LEGALENTITYCLIENT_H
#define LEGALENTITYCLIENT_H

#include <string>
#include "clients/Client.h"
#include "base/Person.h"

using namespace std;

/**
 * @class LegalEntityClient
 * @brief Класс для представления юридических лиц (компаний)
 *
 * Наследуется от Client. Хранит специфическую информацию о юрлице:
 * УНП, регистрационный номер, директора, банковский счет, статус плательщика НДС.
 */
class LegalEntityClient : public Client {
private:
    string companyName; ///< Название компании
    string taxId; ///< УНП/ИНН
    string registrationNumber; ///< Регистрационный номер
    Person* director; ///< Директор
    string bankAccount; ///< Банковский счет
    bool isVatPayer; ///< Плательщик НДС [file:9]

public:
    /**
     * @brief Конструктор по умолчанию
     * Инициализирует базовые поля Client и специфические поля
     */
    LegalEntityClient();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param companyName Название компании
     * @param address Адрес
     * @param registrationDate Дата регистрации
     * @param phone Телефон
     * @param email Email
     * @param taxId УНП/ИНН
     * @param director Директор
     */
    LegalEntityClient(int id,
        const string& companyName,
        Address* address,
        const Date& registrationDate,
        const string& phone,
        const string& email,
        const string& taxId,
        Person* director);

    /** @brief Возвращает название компании */
    const string& getCompanyName() const;
    /** @brief Возвращает УНП/ИНН */
    const string& getTaxId() const;
    /** @brief Возвращает регистрационный номер */
    const string& getRegistrationNumber() const;
    /** @brief Возвращает директора */
    Person* getDirector() const;
    /** @brief Возвращает банковский счет */
    const string& getBankAccount() const;
    /** @brief Возвращает статус плательщика НДС */
    bool getIsVatPayer() const;

    /** @brief Устанавливает название компании (синхронизирует с Client::name) */
    void setCompanyName(const string& value);
    /** @brief Устанавливает УНП/ИНН */
    void setTaxId(const string& value);
    /** @brief Устанавливает регистрационный номер */
    void setRegistrationNumber(const string& value);
    /** @brief Устанавливает директора */
    void setDirector(Person* value);
    /** @brief Устанавливает банковский счет */
    void setBankAccount(const string& value);
    /** @brief Устанавливает статус плательщика НДС */
    void setIsVatPayer(bool value);

    /**
     * @brief Валидация УНП/ИНН
     * @return true если длина от 9 до 12 символов [file:9]
     */
    bool validateTaxId() const;

    /**
     * @brief Краткая информация о компании
     * @return Строка вида "Компания (УНП: xxx), директор: ФИО"
     */
    string getSummaryInfo() const;
};

#endif
