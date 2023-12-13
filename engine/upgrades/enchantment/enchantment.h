#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <list>

#include "../../helps/enums.h"
#include "../../character/enemy/enemy.h"
/*!
 * @brief Класс зачарования
*/
class Enchantment{
    private:
        // Тип зачарования
        std::string enchantment_type;
        // Список коэф. для атаки на фракции врагов
        std::list<std::pair<std::string, double>> coef;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Enchantment() noexcept {}
        Enchantment(std::string et, std::list<std::pair<std::string, double>> c) noexcept: enchantment_type(et), coef(c) {}

        /*!
         * @brief Геттер типа зачарования
         * @return Тип зачарования
         */
        std::string getEnchantment_Type() const noexcept { return enchantment_type; }
        /*!
         * @brief Геттер список коэффициентов
         * @return Список коэффициентов
         */
        std::list<std::pair<std::string, double>> getCoef() const noexcept { return coef; }
        /*!
         * @brief Сеттер типа зачарования
         * @param T Тип зачарования
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
