#ifndef ESTIMATE_H
#define ESTIMATE_H

#include <vector>
#include "documents/Document.h"
#include "repairs/RepairProject.h"
#include "materials/Material.h"

using namespace std;

/**
 * @class Estimate
 * @brief Смета на ремонтные работы
 *
 * Содержит расчет материалов, работ и общей стоимости.
 */
class Estimate : public Document {
private:
    RepairProject* project; ///< Связанный проект
    vector<Material*> materials; ///< Список материалов
    double laborCost; ///< Стоимость работ
    double totalAmount; ///< Общая сумма
    Date validUntil; ///< Действительна до [file:36]

public:
    /** @brief Конструктор по умолчанию */
    Estimate();

    /**
     * @brief Полный конструктор
     * @param id Идентификатор
     * @param created Дата создания
     * @param author Автор
     * @param project Проект
     */
    Estimate(int id,
        const Date& created,
        Employee* author,
        RepairProject* project);

    /** @brief Возвращает проект */
    RepairProject* getProject() const;
    /** @brief Возвращает материалы */
    const vector<Material*>& getMaterials() const;
    /** @brief Возвращает стоимость работ */
    double getLaborCost() const;
    /** @brief Возвращает общую сумму */
    double getTotalAmount() const;
    /** @brief Возвращает дату действия */
    const Date& getValidUntil() const;

    /** @brief Устанавливает стоимость работ */
    void setLaborCost(double value);
    /** @brief Устанавливает дату действия */
    void setValidUntil(const Date& value);

    /** @brief Добавляет материал */
    void addMaterial(Material* material);
    /** @brief Очищает материалы */
    void clearMaterials();
    /** @brief Пересчитывает итог */
    void calculateTotal();

    /** @brief Проверяет просрочку */
    bool isExpired(const Date& today) const;

    /** @brief Краткое содержание */
    string generateSummary() const override;
};

#endif
