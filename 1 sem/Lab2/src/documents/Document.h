#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "base/Date.h"
#include "staff/Employee.h"

using namespace std;

/**
 * @class Document
 * @brief Базовый класс для всех документов системы
 *
 * Абстрактный класс с общей информацией о документе и версионированием.
 */
class Document {
protected:
    int id; ///< Уникальный идентификатор документа
    Date createdDate; ///< Дата создания
    Employee* author; ///< Автор документа
    string status; ///< Статус документа
    int version; ///< Версия документа [file:40]

public:
    /** @brief Конструктор по умолчанию */
    Document();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param createdDate Дата создания
     * @param author Автор
     */
    Document(int id, const Date& createdDate, Employee* author);

    /** @brief Виртуальный деструктор */
    virtual ~Document() = default;

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает дату создания */
    const Date& getCreatedDate() const;
    /** @brief Возвращает автора */
    Employee* getAuthor() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;
    /** @brief Возвращает версию */
    int getVersion() const;

    /** @brief Устанавливает автора */
    void setAuthor(Employee* value);
    /** @brief Устанавливает статус */
    void setStatus(const string& value);

    /** @brief Увеличивает версию */
    void incrementVersion();

    /** @brief Сохранение документа */
    virtual void save();
    /** @brief Архивация документа */
    virtual void markArchived();

    /** @brief Абстрактный метод краткого содержания */
    virtual string generateSummary() const = 0;
};

#endif
