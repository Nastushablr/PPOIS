#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
using namespace std;

/**
 * @class Address
 * @brief Класс для представления полного адреса
 *
 * Хранит все компоненты адреса и предоставляет методы валидации и форматированный вывод.
 */
class Address {
private:
    string street; ///< Улица
    string city; ///< Город
    string postalCode; ///< Почтовый индекс
    string country; ///< Страна
    string building; ///< Номер дома
    string apartment; ///< Номер квартиры

public:
    /**
     * @brief Конструктор по умолчанию
     * Все поля инициализируются пустыми строками
     */
    Address();

    /**
     * @brief Конструктор с параметрами
     * @param street Улица
     * @param city Город
     * @param postalCode Почтовый индекс
     * @param country Страна
     * @param building Номер дома (опционально)
     * @param apartment Номер квартиры (опционально)
     */
    Address(const string& street,
        const string& city,
        const string& postalCode,
        const string& country,
        const string& building = "",
        const string& apartment = "");

    /** @brief Возвращает улицу */
    const string& getStreet() const;
    /** @brief Возвращает город */
    const string& getCity() const;
    /** @brief Возвращает почтовый индекс */
    const string& getPostalCode() const;
    /** @brief Возвращает страну */
    const string& getCountry() const;
    /** @brief Возвращает номер дома */
    const string& getBuilding() const;
    /** @brief Возвращает номер квартиры */
    const string& getApartment() const;

    /** @brief Устанавливает улицу */
    void setStreet(const string& value);
    /** @brief Устанавливает город */
    void setCity(const string& value);
    /** @brief Устанавливает почтовый индекс */
    void setPostalCode(const string& value);
    /** @brief Устанавливает страну */
    void setCountry(const string& value);
    /** @brief Устанавливает номер дома */
    void setBuilding(const string& value);
    /** @brief Устанавливает номер квартиры */
    void setApartment(const string& value);

    /**
     * @brief Формирует полный адрес одной строкой
     * @return Строка вида "street, building, apt. apartment, city postalCode, country"
     */
    string getFullAddress() const;

    /**
     * @brief Проверяет полноту адреса
     * @return true если заполнены street, city, postalCode, country [file:2][file:6]
     */
    bool isValid() const;

    /**
     * @brief Валидация почтового индекса
     * @return true если длина от 4 до 10 символов
     */
    bool validatePostalCode() const;
};

#endif
