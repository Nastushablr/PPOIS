#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "base/Date.h"
#include "repairs/Task.h"

using namespace std;

/**
 * @class Schedule
 * @brief Класс для управления расписанием задач
 *
 * Хранит список задач и предоставляет фильтрацию по дате и статусу.
 */
class Schedule {
private:
    vector<Task*> tasks; ///< Список задач [file:18]

public:
    /** @brief Конструктор по умолчанию */
    Schedule();

    /** @brief Возвращает все задачи */
    const vector<Task*>& getTasks() const;

    /**
     * @brief Добавляет задачу в расписание
     * @param task Указатель на задачу
     */
    void addTask(Task* task);

    /**
     * @brief Удаляет задачу из расписания
     * @param task Указатель на задачу
     */
    void removeTask(Task* task);

    /**
     * @brief Получает задачи на конкретную дату
     * @param date Дата
     * @return Вектор задач на указанную дату
     */
    vector<Task*> getTasksForDate(const Date& date) const;

    /**
     * @brief Подсчет задач по статусу
     * @param status Статус задачи
     * @return Количество задач с данным статусом
     */
    int countTasksByStatus(const string& status) const;
};

#endif
