#include <iostream>
#include <concepts>
#include <type_traits>
#include <functional>

template <typename T1, bool isConst>
/*!
 * @brief Класс итератора для матрицы
 * @tparam T1 адрусуемый итератором тип
 * @tparam isConst итератор является const_iterator если true,
 *                  обычным iterator в ином случае
 */
class Iterator{
    private:
        // Узел, на который указывает итератор
        T1 iter;
    public:
        /*!
         * @brief Тип, обозначающий дистанцию между двумя итераторами,
         *        т.е. результат std::distance(it1, it2)
         */
        typedef std::ptrdiff_t difference_type;
        /*!
         * @brief Адресуемый итератором тип
         */
        typedef T1 value_type;
        /*!
         * @brief Тип указателя на хранимое значение,
         *        для const_iterator - const T*, для обычного - T*
         */
        typedef std::conditional_t<isConst, const T1, T1>* pointer;
        /*!
         * @brief Тип ссылки на хранимое значение,
         *        для const_iterator - const T&, для обычного - T&
         */
        typedef std::conditional_t<isConst, const T1, T1>& reference;
        /*!
         * @brief Категория итератора
         */
        typedef std::contiguous_iterator_tag iterator_category;

        // Итератор противоположной константности
        // может обращаться к privete полям
        friend Iterator<T1, !isConst>;

        /*!
         * @brief Пустой конструктор
         */
        Iterator() noexcept: iter(T1()) {}
        /*!
         * @brief Конструктор по значению
         * @param element Элемент на который указывает итератор
         */
        explicit Iterator(const T1 &element) noexcept: iter(element) {}
        
        /*!
         * @brief Копирующий конструктор
         * @tparam otherConst Константность копируемого иетратора
         * @note Допускает копирование итератора иной константности
         * @note Нельзя из неконстантного в константный
         */
        template<bool otherConst>
        explicit Iterator(const Iterator <T1, otherConst> &I) noexcept requires (isConst >= otherConst): iter(I.iter) {}
        
        /*!
         * @brief Перемещающий конструктор
         * @tparam otherConst Константность перемещающего иетратора
         * @note Допускает перемещение итератора иной константности
         * @note Нельзя из неконстантного в константный
         */
        template<bool otherConst>
        explicit Iterator(const Iterator <T1, otherConst> &&I) noexcept requires (isConst >= otherConst): iter(I.iter){
            I.iter = nullptr;
        }
        /*!
         * @brief Оператор копирования
         * @returns Ссылка на переданный итератор
         * @tparam otherConst Константность копируемого иетратора
         * @note Допускает копирование итератора иной константности
         * @note Нельзя из неконстантного в константный
         */
        template<bool otherConst>
        Iterator& operator =(const Iterator<T1, otherConst>& I) noexcept requires (isConst >= otherConst) {
            if (*this != I){
                iter = I.iter;
            }
            return *this;
        }
        /*!
         * @brief Оператор перемещения
         * @returns Ссылка на переданный итератор
         * @tparam otherConst Константность копируемого иетратора
         * @note Допускает копирование итератора иной константности
         * @note Нельзя из неконстантного в константный
         */
        template<bool otherConst>
        Iterator& operator =(const Iterator<T1, otherConst>&& I) noexcept requires (isConst >= otherConst) {
            if (this != &I){
                iter = I.iter;
                I.iter = nullptr;
            }
            return *this;
        }
        /*!
         * @brief Передвигает итератор на следующий элемент матрицы
         * @returns Ссылка на переданный итератор
         */
        Iterator& operator ++() noexcept {
            ++iter;
            return *this;
        }
        /*!
         * @brief Передвигает итератор на следующий элемент матрицы
         * @returns Состояние итератора до модификации
         */
        Iterator operator ++(int) noexcept {
            Iterator tmp(iter);
            iter++;
            return tmp;
        }
        /*!
         * @brief Передвигает итератор на предыдущий элемент матрицы
         * @returns Ссылка на переданный итератор
         */
        Iterator& operator --() noexcept {
            --iter;
            return *this;
        }
        /*!
         * @brief Передвигает итератор на предыдущий элемент матрицы
         * @returns Состояние итератора до модификации
         */
        Iterator operator --(int) noexcept {
            Iterator tmp(iter);
            iter--;
            return tmp;
        }
        /*!
         * @brief Передвигает итератор на n следующих элементов матрицы
         * @param n Расстояние сдвига
         * @returns Ссылка на переданный итератор
         */
        Iterator& operator +=(difference_type n) noexcept{
            iter += n;
            return *this;
        }
        /*!
         * @brief Передвигает итератор на n предыдущих элементов матрицы
         * @param n Расстояние сдвига
         * @returns Ссылка на переданный итератор
         */
        Iterator& operator -=(difference_type n) noexcept{
            iter -= n;
            return *this;
        }
        /*!
         * @brief Создает итератор через n следующих элементов матрицы
         * @param n Расстояние сдвига
         * @returns Новый итератор
         */
        Iterator operator +(difference_type n) const noexcept {
            return Iterator(iter + n);
        }
        /*!
         * @brief Создает итератор через n предыдущих элементов матрицы
         * @param n Расстояние сдвига
         * @returns Новый итератор
         */
        Iterator operator -(difference_type n) const noexcept {
            return Iterator(iter - n);
        }
        /*!
         * @brief Разыменование
         * @returns Ссылка на адресуемый элемент матрицы
         */
        reference operator *() noexcept{
            return iter;
        }
        /*!
         * @brief Константное разыменование
         * @returns Константная ссылка на адресуемый элемент матрицы
         */
        std::add_const_t<reference> operator *() const noexcept {
            return iter;
        }
        /*!
         * @brief Обрщение к полям элемента
         * @returns Указатель на адресуемый элемент матрицы
         */
        pointer operator ->() const noexcept;

        /*!
         * @brief Разыменование по индексу
         * @param n Индекс
         * @returns Ссылка на адресуемый элемент матрицы
         */
        reference operator[](difference_type n) const noexcept {
            return iter[n];
        }
        /*!
         * @brief Возвращение констнантной ссылки элемента матрицы
         * @returns Ссылка на адресуемый элемент матрицы
         */
        const T1 &Base() const noexcept {
            return iter;
        }
};
/*!
 * @brief Оператор сравнения <
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */
template<typename T1, bool isConst, bool otherConst>
bool operator <(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() < rhs.Base();
}

/*!
 * @brief Оператор сравнения >
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */
template<typename T1, bool isConst, bool otherConst>
bool operator >(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() > rhs.Base();
}

/*!
 * @brief Оператор сравнения <=
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */

template<typename T1, bool isConst, bool otherConst>
bool operator <=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() <= rhs.Base();
}

/*!
 * @brief Оператор сравнения >=
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */
template<typename T1, bool isConst, bool otherConst>
bool operator >=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() >= rhs.Base();
}
/*!
 * @brief Оператор сравнения ==
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */
template<typename T1, bool isConst, bool otherConst>
bool operator ==(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() == rhs.Base();
}
/*!
 * @brief Оператор сравнения !=
 * @returns Истнинность сравнения
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */

template<typename T1, bool isConst, bool otherConst>
bool operator !=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() != rhs.Base();
}

/*!
 * @brief Оператор разности
 * @returns Растстояние между итераторами
 * @tparam isConst Константность первого итератора
 * @tparam otherConst Константность второго итератора
 */
template<typename T1, bool isConst, bool otherConst>
std::ptrdiff_t operator -(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() - rhs.Base();
}

/*!
 * @brief Оператор сложения
 * @returns Новый итератор
 * @tparam isConst Константность первого итератора
 * @param n Сдвиг итератора
 */

template<typename T1, bool isConst>
Iterator<T1, isConst> operator +(std::ptrdiff_t n, const Iterator<T1, isConst> &rhs){
    return Iterator(n + rhs.Base());
}

