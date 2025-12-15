#ifndef PRIVATECLIENT_H
#define PRIVATECLIENT_H

#include <string>
#include "clients/Client.h"
#include "base/Person.h"

using namespace std;

/**
 * @class PrivateClient
 * @brief Класс для представления частных клиентов (физических лиц)
 *
 * Наследуется от Client. Связан с объектом Person, хранит семейное положение
 * и количество иждивенцев. Предоставляет проверку паспортных данных и возраста.
 */
class PrivateClient : public Client {
private:
    Person* person; ///< Связанный объект Person
    string maritalStatus; ///< Семейное положение
    int dependents; ///< Количество иждивенцев [file:7]

public:
    /**
     * @brief Конструктор по умолчанию
     */
    PrivateClient();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param person Объект Person
     * @param address Адрес
     * @param registrationDate Дата регистрации
     * @param phone Телефон
     * @param email Email
     */
    PrivateClient(int id,
        Person* person,
        Address* address,
        const Date& registrationDate,
        const string& phone,
        const string& email);

    /** @brief Возвращает связанный объект Person */
    Person* getPerson() const;
    /** @brief Возвращает семейное положение */
    const string& getMaritalStatus() const;
    /** @brief Возвращает количество иждивенцев */
    int getDependents() const;

    /** @brief Устанавливает объект Person */
    void setPerson(Person* value);
    /** @brief Устанавливает семейное положение */
    void setMaritalStatus(const string& value);
    /** @brief Устанавливает количество иждивенцев */
    void setDependents(int value);

    /**
     * @brief Проверяет наличие действующего паспорта
     * @return true если у Person есть номер паспорта
     */
    bool hasValidPassport() const;

    /**
     * @brief Вычисляет возраст клиента
     * @param today Текущая дата
     * @return Возраст в годах (делегируется Person)
     */
    int getAge(const Date& today) const;
};

#endif
