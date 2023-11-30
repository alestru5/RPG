#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <list>

#include "enums.h"
#include "enemy.h"
/*!
 * @brief Класс зачарования
*/
class Enchantment{
    private:
        // Тип зачарования
        type_enchantment enchantment_type;
        // Список коэф. для атаки на фракции врагов
        std::list<std::pair<trait, double>> coef;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Enchantment() noexcept;
        /*!
         * @brief Конструктор по значению
         * @param N Тип зачарования
         */
        Enchantment(type_enchantment T) noexcept;
        /*!
         * @brief Геттер типа зачарования
         * @return Тип зачарования
         */
        type_enchantment getEnchantment_Type() const noexcept { return enchantment_type; }
        /*!
         * @brief Геттер список коэффициентов
         * @return Список коэффициентов
         */
        std::list<std::pair<trait, double>> getCoef() const noexcept { return coef; }
        /*!
         * @brief Сеттер типа зачарования
         * @param T Тип зачарования
         */
        void setEnchantment_Type(type_enchantment T) noexcept;
        /*!
         * @brief Получение коэффициента атаки по врагу
         * @param enemy Враг
         * @return Коэффициент
         */
        double getMultiply(Enemy *enemy) const noexcept;
        /*!
         * @brief Оператор копирования
         * @param I Другое зачарование
         * @return Ссылка на текущее зачарование
         */
        Enchantment& operator=(const Enchantment& I) noexcept;

};

#endif // ENCHANTMENT_H
