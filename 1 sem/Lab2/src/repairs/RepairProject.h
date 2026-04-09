#ifndef REPAIRPROJECT_H
#define REPAIRPROJECT_H

#include <vector>
#include <string>
#include "base/Date.h"
#include "clients/Client.h"
#include "repairs/RepairObject.h"
#include "repairs/ProjectStage.h"

using namespace std;

class Task;

/**
 * @class RepairProject
 * @brief Основной класс ремонтного проекта
 *
 * Управляет клиентом, объектом ремонта, этапами, задачами, бюджетом и статусом проекта.
 */
class RepairProject {
private:
    int id; ///< Уникальный идентификатор
    Client* client; ///< Клиент
    RepairObject* object; ///< Объект ремонта
    Date startDate; ///< Дата начала
    Date plannedEndDate; ///< Плановая дата окончания
    double budget; ///< Бюджет проекта
    string status; ///< Статус ("planned", "active", "completed")
    vector<ProjectStage*> stages; ///< Этапы проекта
    vector<Task*> tasks; ///< Задачи проекта [file:24]

public:
    /** @brief Конструктор по умолчанию */
    RepairProject();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param client Клиент
     * @param object Объект ремонта
     * @param startDate Дата начала
     * @param budget Бюджет
     */
    RepairProject(int id,
        Client* client,
        RepairObject* object,
        const Date& startDate,
        double budget);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает клиента */
    Client* getClient() const;
    /** @brief Возвращает объект */
    RepairObject* getObject() const;
    /** @brief Возвращает дату начала */
    const Date& getStartDate() const;
    /** @brief Возвращает плановую дату окончания */
    const Date& getPlannedEndDate() const;
    /** @brief Возвращает бюджет */
    double getBudget() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;
    /** @brief Возвращает этапы */
    const vector<ProjectStage*>& getStages() const;
    /** @brief Возвращает задачи */
    const vector<Task*>& getTasks() const;

    /** @brief Устанавливает плановую дату */
    void setPlannedEndDate(const Date& value);
    /** @brief Устанавливает бюджет */
    void setBudget(double value);
    /** @brief Устанавливает статус */
    void setStatus(const string& value);

    /** @brief Добавляет этап */
    void addStage(ProjectStage* stage);
    /** @brief Добавляет задачу */
    void addTask(Task* task);

    /** @brief Рассчитывает прогресс проекта */
    double calculateProgress() const;
    /** @brief Подсчитывает незавершенные задачи */
    int countOpenTasks() const;

    /** @brief Запуск проекта */
    void start();
    /** @brief Завершение проекта */
    void complete();
};

#endif
