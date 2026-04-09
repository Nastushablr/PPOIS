#ifndef TASK_H
#define TASK_H

#include <string>
#include "base/Date.h"
#include "staff/RepairSpecialist.h"
#include "repairs/WorkType.h"

using namespace std;

class RepairProject;

/**
 * @class Task
 * @brief Отдельная задача ремонта
 *
 * Связывает специалиста, тип работ, проект и сроки выполнения.
 */
class Task {
private:
    int id; ///< Уникальный идентификатор
    RepairProject* project; ///< Связанный проект
    RepairSpecialist* specialist; ///< Назначенный специалист
    WorkType* workType; ///< Тип работ
    string description; ///< Описание
    string status; ///< Статус ("planned", "in_progress", "completed")
    int priority; ///< Приоритет (1-5)
    Date plannedDate; ///< Плановая дата
    Date completedDate; ///< Фактическая дата завершения [file:27]

public:
    /** @brief Конструктор по умолчанию */
    Task();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param project Проект
     * @param specialist Специалист
     * @param workType Тип работ
     * @param description Описание
     * @param priority Приоритет
     * @param plannedDate Плановая дата
     */
    Task(int id,
        RepairProject* project,
        RepairSpecialist* specialist,
        WorkType* workType,
        const string& description,
        int priority,
        const Date& plannedDate);

    /** @brief Возвращает ID */
    int getId() const;
    /** @brief Возвращает проект */
    RepairProject* getProject() const;
    /** @brief Возвращает специалиста */
    RepairSpecialist* getSpecialist() const;
    /** @brief Возвращает тип работ */
    WorkType* getWorkType() const;
    /** @brief Возвращает описание */
    const string& getDescription() const;
    /** @brief Возвращает статус */
    const string& getStatus() const;
    /** @brief Возвращает приоритет */
    int getPriority() const;
    /** @brief Возвращает плановую дату */
    const Date& getPlannedDate() const;
    /** @brief Возвращает дату завершения */
    const Date& getCompletedDate() const;

    /** @brief Назначает специалиста */
    void setSpecialist(RepairSpecialist* value);
    /** @brief Устанавливает тип работ */
    void setWorkType(WorkType* value);
    /** @brief Устанавливает описание */
    void setDescription(const string& value);
    /** @brief Устанавливает приоритет */
    void setPriority(int value);
    /** @brief Устанавливает плановую дату */
    void setPlannedDate(const Date& value);

    /** @brief Запуск задачи */
    void start();
    /** @brief Завершение задачи */
    void complete(const Date& date);
    /** @brief Проверяет завершенность */
    bool isCompleted() const;
};

#endif
