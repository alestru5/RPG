#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <iostream>
#include <list>

#include "../../helps/enums.h"

class Hero;
/*!
 * @brief Класс артефакта
 */
class Artifact{
    protected:
        // Тип артефакта
        std::string artifact_type;
        // Изменения характеристик, которые дает артефакт
        std::list<std::pair<std::string, int>> changes;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Artifact() noexcept {}
        Artifact(std::string at, std::list<std::pair<std::string, int>> c) noexcept: artifact_type(at), changes(c) {}
        /*!
         * @brief Геттер типа артефакта
         * @return Тип артефакта
         */
        std::string getArtifact_Type() const noexcept { return artifact_type; }
        /*!
         * @brief Геттер списка изменений
         * @return Список изменений
         */
        std::list<std::pair<std::string, int>> getChanges() const noexcept { return changes; }
        /*!
         * @brief Применение изменений на героя
         * @param H Герой
         */
        void useChanges(Hero &H) const noexcept;
        /*!
         * @brief Отмена применений изменений на героя
         * @param H Герой
         */
        void unUseChanges(Hero &H) const noexcept;
        /*!
         * @brief Оператор копирования
         * @param I Другой артифакт
         * @return Ссылка на текущий артифакт
         */
        Artifact& operator=(const Artifact& I) noexcept;
};

#endif // ARTIFACT_H

