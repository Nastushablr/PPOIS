#ifndef REPAIRFIRMEXCEPTIONS_H
#define REPAIRFIRMEXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

/**
 * @file RepairFirmExceptions.h
 * @brief Набор исключений для системы ремонтной компании
 *
 * Содержит специализированные исключения для обработки ошибок валидации
 * и бизнес-логики системы.
 */

 /**
  * @class InvalidPersonDataException
  * @brief Исключение для некорректных персональных данных
  *
  * Используется при валидации Person: неверный email, паспорт, возраст и т.д.
  */
class InvalidPersonDataException : public runtime_error {
public:
    /**
     * @brief Конструктор
     * @param msg Текст ошибки
     */
    explicit InvalidPersonDataException(const string& msg);
};

/**
 * @class InvalidAddressException
 * @brief Исключение для некорректного адреса
 *
 * Неверный почтовый индекс, пустые обязательные поля адреса.
 */
class InvalidAddressException : public runtime_error {
public:
    explicit InvalidAddressException(const string& msg);
};

/**
 * @class InvalidDateException
 * @brief Исключение для некорректной даты
 *
 * Невалидная дата (неправильный день/месяц), дата из будущего/прошлого.
 */
class InvalidDateException : public runtime_error {
public:
    explicit InvalidDateException(const string& msg);
};

/**
 * @class InvalidClientException
 * @brief Исключение для некорректного клиента
 *
 * Неверные данные клиента, дублирование ID, проблемы с типом клиента.
 */
class InvalidClientException : public runtime_error {
public:
    explicit InvalidClientException(const string& msg);
};

/**
 * @class InvalidEmployeeException
 * @brief Исключение для некорректного сотрудника
 *
 * Неверные данные сотрудника, дублирование, несоответствие должности.
 */
class InvalidEmployeeException : public runtime_error {
public:
    explicit InvalidEmployeeException(const string& msg);
};

/**
 * @class InvalidProjectException
 * @brief Исключение для некорректного проекта
 *
 * Неверные параметры проекта, конфликты сроков, превышение бюджета.
 */
class InvalidProjectException : public runtime_error {
public:
    explicit InvalidProjectException(const string& msg);
};

/**
 * @class InsufficientMaterialException
 * @brief Исключение недостатка материалов
 *
 * Недостаточно материалов на складе для выполнения задачи.
 */
class InsufficientMaterialException : public runtime_error {
public:
    explicit InsufficientMaterialException(const string& msg);
};

/**
 * @class InvalidPaymentException
 * @brief Исключение для некорректного платежа
 *
 * Неверная сумма, просроченный счет, дублирование платежа.
 */
class InvalidPaymentException : public runtime_error {
public:
    explicit InvalidPaymentException(const string& msg);
};

/**
 * @class InsufficientFundsException
 * @brief Исключение недостатка средств
 *
 * Недостаточно средств на счете для операции.
 */
class InsufficientFundsException : public runtime_error {
public:
    explicit InsufficientFundsException(const string& msg);
};

/**
 * @class ScheduleConflictException
 * @brief Исключение конфликта расписания
 *
 * Пересечение задач специалиста, нехватка ресурсов по времени.
 */
class ScheduleConflictException : public runtime_error {
public:
    explicit ScheduleConflictException(const string& msg);
};

/**
 * @class ContractViolationException
 * @brief Исключение нарушения договора
 *
 * Нарушение условий договора, превышение сроков/бюджета.
 */
class ContractViolationException : public runtime_error {
public:
    explicit ContractViolationException(const string& msg);
};

/**
 * @class OperationNotAllowedException
 * @brief Исключение запрета операции
 *
 * Операция запрещена статусом документа/проекта/сотрудника.
 */
class OperationNotAllowedException : public runtime_error {
public:
    explicit OperationNotAllowedException(const string& msg);
};

#endif
