#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <iostream>
#include <list>

#include "../../helps/enums.h"
#include "../../helps/sets/setchanges.h"

class Hero;
/*!
 * @brief Класс артефакта
 */
class Artifact{
    protected:
        // Тип артефакта
        type_artifact artifact_type;
        // Изменения характеристик, которые дает артефакт
        std::list<std::pair<short_characteristic, int>> changes;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Artifact() noexcept;
        /*!
         * @brief Конструктор по значению
         * @param A Тип артефакта
         */
        Artifact(type_artifact T) noexcept;
        /*!
         * @brief Геттер типа артефакта
         * @return Тип артефакта
         */
        type_artifact getArtifact_Type() const noexcept { return artifact_type; }
        /*!
         * @brief Геттер списка изменений
         * @return Список изменений
         */
        std::list<std::pair<short_characteristic, int>> getChanges() const noexcept {return changes; }
        /*!
         * @brief Сеттер типа артефакта
         * @param T Тип артефакта
         */
        void SetArtifact_Type(type_artifact T) noexcept;

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

