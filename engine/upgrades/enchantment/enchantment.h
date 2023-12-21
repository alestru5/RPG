#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <list>
#include <string>

/*!
 * @brief Класс зачарования
*/
class Enchantment{
    protected:
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
        double getMultiply() const noexcept;
        /*!
         * @brief Оператор копирования
         * @param I Другое зачарование
         * @return Ссылка на текущее зачарование
         */
        void setAllC(std::string et, double c) noexcept;
        Enchantment& operator=(const Enchantment& I) noexcept;

};

#endif // ENCHANTMENT_H
