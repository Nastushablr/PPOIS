#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "base/Address.h"
#include "base/Date.h"

using namespace std;

/**
 * @class Client
 * @brief Базовый класс для представления клиентов системы
 *
 * Содержит общую информацию о клиенте: идентификатор, контакты, адрес,
 * дату регистрации, статус и общую сумму расходов. Предоставляет базовые
 * операции управления клиентом (регистрация, блокировка, деактивация).
 */
class Client {
protected:
    int id; ///< Уникальный идентификатор клиента
    string name; ///< Название/имя клиента
    Address* address; ///< Адрес клиента
    Date registrationDate; ///< Дата регистрации
    string phone; ///< Телефон
    string email; ///< Email
    string status; ///< Статус клиента
    double totalSpent; ///< Общая сумма расходов [file:8]

public:
    /**
     * @brief Конструктор по умолчанию
     * Инициализирует поля значениями по умолчанию
     */
    Client();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param name Название/имя
     * @param address Адрес
     * @param registrationDate Дата регистрации
     * @param phone Телефон
     * @param email Email
     */
    Client(int id,
        const string& name,
        Address* address,
        const Date& registrationDate,
        const string& phone,
        const string& email);

    /** @brief Виртуальный деструктор */
    virtual ~Client() = default;

    /** @brief Возвращает ID клиента */
    int getId() const;
    /** @brief Возвращает название/имя */
    const string& getName() const;
    /** @brief Возвращает адрес */
    Address* getAddress() const;
    /** @brief Возвращает дату регистрации */
    const Date& getRegistrationDate() const;
    /** @brief Возвращает телефон */
    const string& getPhone() const;
    /** @brief Возвращает email */
    const string& getEmail() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;
    /** @brief Возвращает общую сумму расходов */
    double getTotalSpent() const;

    /** @brief Устанавливает название/имя */
    void setName(const string& value);
    /** @brief Устанавливает адрес */
    void setAddress(Address* value);
    /** @brief Устанавливает телефон */
    void setPhone(const string& value);
    /** @brief Устанавливает email */
    void setEmail(const string& value);
    /** @brief Устанавливает статус */
    void setStatus(const string& value);

    /**
     * @brief Регистрация клиента (виртуальный метод)
     * Переопределяется в наследниках
     */
    virtual void registerClient();

    /** @brief Деактивация клиента (виртуальный метод) */
    virtual void deactivate();

    /** @brief Блокировка клиента (виртуальный метод) */
    virtual void block();

    /**
     * @brief Обновление контактных данных (виртуальный метод)
     * @param newPhone Новый телефон
     * @param newEmail Новый email
     */
    virtual void updateContacts(const string& newPhone,
        const string& newEmail);

    /**
     * @brief Добавляет сумму к общим расходам
     * @param amount Сумма расходов
     */
    void addSpent(double amount);
};

#endif
