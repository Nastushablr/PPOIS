#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"

using namespace std;

/**
 * @class Person
 * @brief Класс для представления персональных данных человека
 *
 * Содержит основные данные о человеке, включая паспортные данные и контактную информацию.
 * Поддерживает вычисление возраста и валидацию email.
 */
class Person {
private:
    int id; ///< Уникальный идентификатор
    string firstName; ///< Имя
    string lastName; ///< Фамилия
    Date birthDate; ///< Дата рождения
    string phone; ///< Телефон
    string email; ///< Email
    string passportNumber; ///< Номер паспорта
    string nationality; ///< Гражданство

public:
    /**
     * @brief Конструктор по умолчанию
     * Все поля инициализируются значениями по умолчанию
     */
    Person();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param firstName Имя
     * @param lastName Фамилия
     * @param birthDate Дата рождения
     * @param phone Телефон
     * @param email Email
     * @param passportNumber Номер паспорта
     * @param nationality Гражданство (опционально)
     */
    Person(int id,
        const string& firstName,
        const string& lastName,
        const Date& birthDate,
        const string& phone,
        const string& email,
        const string& passportNumber,
        const string& nationality = "");

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает имя */
    const string& getFirstName() const;
    /** @brief Возвращает фамилию */
    const string& getLastName() const;
    /** @brief Возвращает дату рождения */
    const Date& getBirthDate() const;
    /** @brief Возвращает телефон */
    const string& getPhone() const;
    /** @brief Возвращает email */
    const string& getEmail() const;
    /** @brief Возвращает номер паспорта */
    const string& getPassportNumber() const;
    /** @brief Возвращает гражданство */
    const string& getNationality() const;

    /** @brief Устанавливает имя */
    void setFirstName(const string& value);
    /** @brief Устанавливает фамилию */
    void setLastName(const string& value);
    /** @brief Устанавливает дату рождения */
    void setBirthDate(const Date& value);
    /** @brief Устанавливает телефон */
    void setPhone(const string& value);
    /** @brief Устанавливает email */
    void setEmail(const string& value);
    /** @brief Устанавливает номер паспорта */
    void setPassportNumber(const string& value);
    /** @brief Устанавливает гражданство */
    void setNationality(const string& value);

    /**
     * @brief Полное имя
     * @return "Имя Фамилия"
     */
    string getFullName() const;

    /**
     * @brief Вычисляет возраст
     * @param today Текущая дата
     * @return Возраст в годах (учитывает день рождения) [file:1][file:5]
     */
    int getAge(const Date& today) const;

    /**
     * @brief Простая валидация email
     * @return true если содержит @ и . после него
     */
    bool validateEmail() const;

    /**
     * @brief Обновляет контактные данные
     * @param newPhone Новый телефон
     * @param newEmail Новый email
     */
    void updateContact(const string& newPhone,
        const string& newEmail);
};

#endif
