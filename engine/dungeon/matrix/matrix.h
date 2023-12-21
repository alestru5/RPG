#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <concepts>
#include <type_traits>
#include <limits>

#include "iterator.h"
#include "../cell/cell.h"

/*!
 * @brief Матрица
 * @tparam T Тип хранимых значений
 */
template <typename T>
class Matrix{
    /*!
     * @brief Тип хранимых значений
     */
    typedef std::allocator_traits<std::allocator<T>>::value_type valuetype;
    /*!
     * @brief Указатель на тип хранимых значений
     */
    typedef std::allocator_traits<std::allocator<T>>::pointer pointer;
    /*!
     * @brief Констнантный указатель на тип хранимых значений
     */
    typedef std::allocator_traits<std::allocator<T>>::const_pointer const_pointer;
    /*!
     * @brief Ссылка на тип хранимых значений
     */
    typedef valuetype& reference;
    /*!
     * @brief Константная ссылка на тип хранимых значений
     */
    typedef const valuetype& const_reference;
    /*!
     * @brief Тип итератора
     */
    typedef Iterator<pointer, false> iterator;
    /*!
     * @brief Тип константного итератора
     */
    typedef Iterator<pointer, true> const_iterator;
    /*!
     * @brief Тип, обозначающий дистанцию между двумя итераторами, т.е. результат std::distance(it1, it2)
     */
    typedef std::ptrdiff_t different_type;
    /*!
     * @brief Тип, используемый для преставления размера контейнера
     */
    typedef std::allocator_traits<std::allocator<T>>::size_type size_type;

private:
    //Максимальный размер матрицы
    int max_size;
    //Количество строк
    int m;
    //Количество столбцов
    int n;
    //Матрица,, представленная вектором
    pointer matrix = nullptr;

public:
    /*!
     * @brief Класс специального итератора для списка
     *         с предикатом
     */
    class SpecialIterator {
        private:
            // Матрица, к которой привязан итератор
            Matrix<T> &matrix;
            // Индекс элемента итератора
            int index;
            // Предикатная функция
            std::function<bool(Cell С, int i)> foo;
        public:
            /*!
             * @brief Тип, обозначающий дистанцию между двумя итераторами,
             *        т.е. результат std::distance(it1, it2)
             */
            typedef std::ptrdiff_t difference_type;
            /*!
             * @brief Адресуемый итератором тип
             */
            typedef T value_type;
            /*!
             * @brief Тип указателя на хранимое значение,
             */
            typedef T* pointer;
            /*!
             * @brief Тип ссылки на хранимое значение,
             */
            typedef T& reference;
            /*!
             * @brief Категория итератора
             */
            typedef std::contiguous_iterator_tag iterator_category;

            /*!
             * @brief Конструктор по значению
             * @param M Матрица, к которой привязан итератор
             * @param ind Индекс элемента итератора
             */
            SpecialIterator(Matrix<T> &M, int ind) : matrix(M), index(ind), foo( [](Cell C, int i){ return true; }) {}
            /*!
             * @brief Конструктор по значению
             * @param M Матрица, к которой привязан итератор
             * @param ind Индекс элемента итератора
             * @param F Предикатная функция
             */
            SpecialIterator(Matrix<T> &M, int ind, std::function<bool(Cell С, int i)>& F) : matrix(M), index(ind), foo(F) {
                while (!foo(static_cast<Cell>(matrix.matrix[index]), index) && index < matrix.getM() * matrix.getN()){
                    index += 1;
                }
                if (index + 1 == matrix.getM() * matrix.getN() && !foo(static_cast<Cell>(matrix.matrix[index]), index)){
                    index += 1;
                }
            }
            /*!
             * @brief Передвигает итератор на следующий элемент матрицы, по предикату
             * @returns Ссылка на переданный итератор
             */
            SpecialIterator &operator++() {
                index += 1;
                while (!foo(static_cast<Cell>(matrix.matrix[index]), index) && index < matrix.getM() * matrix.getN()){
                    index += 1;
                }
                if (index + 1 == matrix.getM() * matrix.getN() && !foo(static_cast<Cell>(matrix.matrix[index]), index)){
                    index += 1;
                }
                return *this;
            }
            /*!
             * @brief Передвигает итератор на следующий элемент матрицы по предикату
             * @returns Состояние итератора до модификации
             */
            SpecialIterator operator++(int) {
                SpecialIterator tmp = *this;
                ++(*this);
                return tmp;
            }
            /*!
             * @brief Оператор сравнения ==
             * @returns Истнинность сравнения
             * @param other Второй итератор
             */
            bool operator==(const SpecialIterator &other) const {
                return index == other.index;
            }
            /*!
             * @brief Оператор сравнения !=
             * @returns Истнинность сравнения
             * @param otherConst Второй итератор
             */

            bool operator!=(const SpecialIterator &other) const {
                return index != other.index;
            }
            /*!
             * @brief Разыменование
             * @returns Ссылка на адресуемый элемент матрицы
             */

            reference operator *() noexcept{
                return matrix.matrix[index];
            }
    };
    /*!
     * @brief Класс строки матрицы
     */
    class MatrixRow {
    private:
        //Размер строки
        int size;
        // Строка матрицы
        pointer row;
    public:
        /*!
         * @brief Конструктор по значению
         * @param r Строка матрицы
         * @param n Размер строки
         */
        MatrixRow(pointer r, int n): row(r), size(n){}
        /*!
         * @brief Оператор получения элемента по индексу
         * @param index Индекс
         * @throw InvalidArgument Некорректный индекс
         */
        T& operator[](int index) {
            if (index >= size || index < 0){
                throw std::invalid_argument("index out of range");
            }
            return row[index];
        }
    };
    /*!
     * @brief Пустой конструктор, создаёт пустую матрицу
     */
    Matrix() noexcept (std::is_nothrow_default_constructible_v<T>): m(0), n(0), max_size(1000 * 1000), matrix(new valuetype[max_size]) {}
    /*!
     * @brief Копирующий конструктор
     * @param M Копируемая матрица
     */
    Matrix(const Matrix &M) requires std::copy_constructible<T>: Matrix() {
        m = M.m;
        n = M.n;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                matrix[i * n + j] = M.matrix[i * n + j];
            }
        }
    }
    /*!
     * @brief Конструктор по значению, заполняющий одинаковыми элементами
     * @param i Число строк
     * @param j число столбцов
     * @param val Число котором заполнить матрицу
     */
    Matrix(const int i, const int j, valuetype val) noexcept: Matrix(){
        if (i > 0 && j > 0 && i * j < max_size){
            m = i;
            n = j;
            for (int k = 0; k < m * n; k++){
                matrix[k] = val;
            }
        }
    }
    /*!
     * @brief Перемещающий конструктор
     * @param M Перемещаемая матрица
     */
    Matrix(Matrix &&M) requires std::copy_constructible<T>: Matrix() {
        swap(M);
    }
    /*!
     * @brief Конструктор, заполняющий список n копиями t
     * @param n Количество элементов
     * @param t Значение элемента, которым будет заполнен список
     */
    Matrix(size_type n, const pointer&t) requires std::copy_constructible<T>: Matrix() {
        insert_rows(end(), n, t);
    }
    /*!
     * @brief Конструктор, заполняющий список элементами из диапазона [i, j)
     * @param i Начало диапазона для копирования
     * @param j Конец диапазона для копирования
     */
    template<std::input_iterator It>
    Matrix(It i, It j) requires std::constructible_from<pointer, std::iter_reference_t<It>>: Matrix(){
        insert_rows(end(), i, j);
    }
    /*!
     * @brief Конструктор, заполняющий список элементами из списка инициализации
     * @param il inisializer_list, из которого будут скопированы значения
     */
    Matrix(std::initializer_list<T> il) requires std::move_constructible<T>: Matrix(){
        insert_rows(end(), std::move(il));
    }
    /*!
     * @brief Конструктор, заполняющий список элементами из двойного вектора
     * @param data двойной вектор, из которого будут скопированы значения
     */
    Matrix(std::vector<std::vector<T>> &data) noexcept{
        max_size = 1000 * 1000;
        matrix = new valuetype[max_size];
        if (data.size() == 0){
            m = 0;
            n = 0;
        } else{
            m = data.size();
            n = data[0].size();
        }
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                matrix[i * n + j] = data[i][j];
            }
        }
    }
    /*!
     * @brief Деструктор
     */
    ~Matrix() {
        clear();
    }

    pointer allocate(pointer P){
        return P;
    }
    /*!
     * @brief Вставка строки перед позицией pos
     * @param pos Номер строки
     * @param next Строка
     */
    void insert_row(const int pos, valuetype* next){

        if (pos >= 0 && pos % n == 0 && pos <= m && (m + 1) * n <= max_size){
            for (int i = 0; i < n; i++){
                for (int j = m * n + i; j > n * pos + i; j--){
                    matrix[j] = matrix[j - 1];
                }
            }
            for (int i = 0; i < n; i ++){
                matrix[n * pos + i] = next[i];
            }
            m += 1;
        }
    }
    /*!
     * @brief Вставка столбца на позицию pos
     * @param pos Номер столбца
     * @param next Строка
     */
    void insert_col(const int pos, valuetype* next){
        if (pos >= 0 && pos <= n && (n + 1) * m <= max_size){
            for (int i = 0; i < m; i++){
                for (int j = n * m + m - 1; j > pos; j--){
                    matrix[i * n + j + i] = matrix[i * n + j + i - 1];
                }
                matrix[i * n + pos + i] = next[i];
            }
            n += 1;
        }
    }
    /*!
     * @brief Удаление строки по позиции pos
     * @param pos Номер строки
     */
    void erase_row(const int pos){
        if (pos >= 0 && pos < m){
            for (int i = pos; i < m - 1; i++){
                for (int j = 0; j < n; j++){
                    matrix[i * n + j] = matrix[i * n + j + n];
                }
            }
            m -= 1;
        }
    }
    /*!
     * @brief Удаление столбца по позиции pos
     * @param pos Номер столбца
     */
    void erase_col(const int pos){
        if (pos >= 0 && pos < n){
            for (int i = 0; i < m; i++){
                for (int j = pos; j < n * m; j++){
                    matrix[i * n + j - i] = matrix[i * n + j + 1 - i];
                }
            }
            n -= 1;
        }
    }

    /*!
     * @brief Геттер числа строк
     */
    int getM() const noexcept { return m; }
    /*!
     * @brief Геттер числа столбцов
     */
    int getN() const noexcept { return n; }
    /*!
     * @brief Геттер матрицы
     */
    T* getMatrix() noexcept { return matrix; }

    T& getter(int a, int b) { return matrix[a * n + b]; }
    /*!
     * @brief Копирующий оператор присваивания
     * @param o Копируемая матрица
     */
    Matrix& operator = (Matrix& o) requires std::copy_constructible<T> {
        if (this == &o){
            return *this;
        }
        clear();
        m = o.m;
        n = o.n;
        max_size = 100 * 100;
        matrix = new valuetype[max_size];
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                matrix[i * n + j] = o[i][j];
            }
        }
        return *this;
    }
    /*!
     * @brief Перемещающий оператор присваивания
     * @param o Перемещаемая матрица
     */
    Matrix& operator = (Matrix&& o) noexcept {

        swap(o);
        return *this;
    }
    /*!
     * @brief Оператор присваивания, заполняющий матрицу элементами из списка инициализации
     * @param il inisializer_list, из которого будут скопированы значения
     */
    Matrix& operator = (std::initializer_list<T> il) requires std::move_constructible<T>{

        assign(std::move(il));
        return *this;
    }

    /*!
     * @brief Оператор получения строки по индексу
     * @param index Индекс
     * @throw InvalidArgument Некорректный индекс
     */
    MatrixRow operator [](int index){
        if (index >= m || index <0){
            throw std::invalid_argument("index out of range");
        }
        return MatrixRow(&matrix[index * n], n);
    }

    /*!
     * @brief Вставка в матрицу строки, сконструированную из переданных значений
     * @param p Итератор, перед которым будет вставлена строка
     * @param args Значения для передачи в конструктор элемента
     * @returns Итератор на вставленный элемент
     */
    template<typename ...Args>
    iterator emplace_rows(iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{

        if((p -begin()) % n != 0) {

            return iterator(const_cast<valuetype*>(p.iter));
        }
        pointer tmp = allocate(args...);

        insert_row((p -begin()) / n, tmp);
        return iterator(tmp);
    }
    /*!
     * @brief Вставка в матрицу строки, сконструированную из переданных значений
     * @param p Константный итератор, перед которым будет вставлена строка
     * @param args Значения для передачи в конструктор элемента
     * @returns Итератор на вставленный элемент
     */
    template<typename ...Args>
    iterator emplace_rows(const_iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{

        if((p - begin()) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        pointer tmp = allocate(args...);
        insert_row((p - begin()) / n, tmp);
        return iterator(tmp);
    }
    /*!
     * @brief Вставка в матрицу столбца, сконструированного из переданных значений
     * @param p Итератор, перед которым будет вставлен новый столбец
     * @param args Значения для передачи в конструктор элемента
     * @returns Итератор на вставленный элемент
     */
    template<typename ...Args>
    iterator emplace_cols(iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
        if(p - begin() > n) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        pointer tmp = allocate(args...);
        insert_col(p -begin(), tmp);
        return iterator(tmp);
    }
    /*!
     * @brief Вставка в матрицу столбца, сконструированного из переданных значений
     * @param p Констнантный итератор, перед которым будет вставлен новый столбец
     * @param args Значения для передачи в конструктор элемента
     * @returns Итератор на вставленный элемент
     */
    template<typename ...Args>
    iterator emplace_cols(const_iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
        if(p -begin() > n) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        pointer tmp = allocate(args...);
        insert_col(p - begin(), tmp);
        return iterator(tmp);
    }
    /*!
     * @brief Вставка в матрицу копии переданной строки
     * @param p Итератор, перед которым будет вставлена строка
     * @param t Строка для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_rows(iterator p, const pointer& t) requires std::copy_constructible<T>{
        return emplace_rows(p, t);
    }
    /*!
     * @brief Вставка в матрицу копии переданной строки
     * @param p Константный итератор, перед которым будет вставлена строка
     * @param t Строка для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_rows(const_iterator& p, const pointer& t) requires std::copy_constructible<T>{
        return emplace_rows(p, t);
    }
    /*!
     * @brief Вставка в матрицу копии переданного столбца
     * @param p Итератор, перед которым будет вставлен столбец
     * @param t Столбец для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_cols(iterator p, const pointer& t) requires std::copy_constructible<T>{
        return emplace_cols(p, t);
    }
    /*!
     * @brief Вставка в матрицу копии переданного столбца
     * @param p Константный итератор, перед которым будет вставлен столбец
     * @param t Столбец для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_cols(const_iterator p, const pointer& t) requires std::copy_constructible<T>{
        return emplace_cols(p, t);
    }
    /*!
     * @brief Вставка в матрицу переданной строки при помощи перемещения
     * @param p Итератор, перед которым будет вставлена строка
     * @param t Строка для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_rows(iterator p, pointer&& t) requires std::move_constructible<T> {
        return emplace_rows(p, std::move(t));
    }
    /*!
     * @brief Вставка в матрицу переданной строки при помощи перемещения
     * @param p Константный итератор, перед которым будет вставлена строка
     * @param t Строка для вставки
     * @returns Итератор на вставленный элемент
     */

    iterator insert_rows(const_iterator p, pointer&& t) requires std::move_constructible<T> {
        return emplace_rows(p, std::move(t));
    }
    /*!
     * @brief Вставка в матрицу переданного столбца при помощи перемещения
     * @param p Итератор, перед которым будет вставлен столбец
     * @param t Столбец для вставки
     * @returns Итератор на вставленный элемент
     */

    iterator insert_cols(iterator p, pointer&& t) requires std::move_constructible<T> {
        return emplace_cols(p, std::move(t));
    }
    /*!
     * @brief Вставка в матрицу переданного столбца при помощи перемещения
     * @param p Константный итератор, перед которым будет вставлен столбец
     * @param t Столбец для вставки
     * @returns Итератор на вставленный элемент
     */
    iterator insert_cols(const_iterator p, pointer&& t) requires std::move_constructible<T> {
        return emplace_cols(p, std::move(t));
    }
    /*!
     * @brief Вставка в матрицу с копий строки t
     * @param p Итератор, перед которым будут вставлены строки
     * @param c Количество значений для вставки
     * @param t Строка для вставки
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_rows(iterator p, size_type c, const pointer& t) requires std::copy_constructible<T> {
        if (n == 0){
            n = c;
        }
        if(n == 0 || (p - begin()) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        for(size_t i = 0; i < c; ++i){
            insert_rows(p, t);
        }
        return iterator((p-n*c).iter);
    }
    /*!
     * @brief Вставка в матрицу с копий строки t
     * @param p Константный итератор, перед которым будут вставлены строки
     * @param c Количество значений для вставки
     * @param t Строка для вставки
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_rows(const_iterator p, size_type c, const pointer& t) requires std::copy_constructible<T> {
        if (n == 0){
            n = c;
        }
        if(n == 0 || (p -begin()) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        for(size_t i = 0; i < c; ++i){
            insert_rows(p, t);
        }
        return iterator((p-n*c).iter);
    }
    /*!
     * @brief Вставка в матрицу с копий столбца t
     * @param p Итератор, перед которым будут вставлены столбцы
     * @param c Количество значений для вставки
     * @param t Столбец для вставки
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_cols(iterator p, size_type c, const pointer& t) requires std::copy_constructible<T> {
        if (m == 0){
            m = c;
        }
        if(n == 0 || p - begin() > n) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        for(size_t i = 0; i < c; ++i){
            insert_cols(p, t);
        }
        return iterator((p-c).iter);
    }
    /*!
     * @brief Вставка в матрицу с копий столбца t
     * @param p Константный итератор, перед которым будут вставлены столбцы
     * @param c Количество значений для вставки
     * @param t Столбец для вставки
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_cols(const_iterator p, size_type c, const pointer& t) requires std::copy_constructible<T> {
        if (m == 0){
            m = c;
        }
        if(n == 0 || p - begin() > n) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        for(size_t i = 0; i < c; ++i){
            insert_cols(p, t);
        }
        return iterator((p-c).iter);
    }
    /*!
     * @brief Вставка в матрицу строк элементов из диапазона [i, j)
     * @param p Итератор, перед которым будут вставлены строки
     * @param i Начало диапазона
     * @param j Конец диапазона
     * @returns Итератор на последний вставленный элемент
     */
    template<std::input_iterator It>
    iterator insert_rows(iterator p, It i, It j) requires std::copy_constructible<T>{
        if (n == 0){
            n = j - i;
        }
        if(i == j || (j - i) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        while(i != j){
            valuetype *tmp = new valuetype[n];
            for (int z = 0; z < n; z++){
                tmp[z] = **i;
                i += 1;
            }
            insert_rows(p, tmp);
        }
        return iterator((p-(j-i)).iter);
    }
    /*!
     * @brief Вставка в матрицу строк элементов из диапазона [i, j)
     * @param p Константный итератор, перед которым будут вставлены строки
     * @param i Начало диапазона
     * @param j Конец диапазона
     * @returns Итератор на последний вставленный элемент
     */
    template<std::input_iterator It>
    iterator insert_rows(const_iterator p, It i, It j) requires std::copy_constructible<T>{
        if (n == 0){
            n = j - i;
        }
        if(i == j || (j - i) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        while(i != j){
            valuetype *tmp = new valuetype[n];
            for (int z = 0; z < n; z++){
                tmp[z] = **i;
                i += 1;
            }
            insert_rows(p, tmp);
        }
        return iterator((p-(j-i)).iter);
    }
    /*!
     * @brief Вставка в матрицу столбцов элементов из диапазона [i, j)
     * @param p Итератор, перед которым будут вставлены столбцы
     * @param i Начало диапазона
     * @param j Конец диапазона
     * @returns Итератор на последний вставленный элемент
     */
    template<std::input_iterator It>
    iterator insert_cols(iterator p, It i, It j) requires std::copy_constructible<T>{
        if (m == 0){
            m = j - i;
        }
        if(i == j || (j - i) % m != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        int l = 0;
        while(i != j){
            valuetype *tmp = new valuetype[m];
            for (int z = 0; z < m; z++){
                tmp[z] = **i;
                i += 1;
            }
            l += 1;
            insert_cols(p, tmp);
        }
        return iterator((p-l).iter);
    }
    /*!
     * @brief Вставка в матрицу столбцов элементов из диапазона [i, j)
     * @param p Константный итератор, перед которым будут вставлены столбцы
     * @param i Начало диапазона
     * @param j Конец диапазона
     * @returns Итератор на последний вставленный элемент
     */
    template<std::input_iterator It>
    iterator insert_cols(const_iterator p, It i, It j) requires std::copy_constructible<T>{
        if (m == 0){
            m = j - i;
        }
        if(i == j || (j - i) % m != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        int l = 0;
        while(i != j){
            valuetype *tmp = new valuetype[m];
            for (int z = 0; z < m; z++){
                tmp[z] = **i;
                i += 1;
            }
            l += 1;
            insert_cols(p, tmp);
        }
        return iterator((p-l).iter);
    }
    /*!
     * @brief Вставка в матрицу строк элементов из спска инициалазации
     * @param p Мтератор, перед которым будут вставлены строки
     * @param il Список инициализации
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_rows(iterator p, std::initializer_list<T> il) requires std::move_constructible<T> {
        if (n == 0){
            n = il.end() - il.begin();
        }
        if(il.end() == il.begin() || (il.end() - il.begin()) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }
        auto i = il.begin();
        while (i != il.end()){
            valuetype *tmp = new valuetype[n];
            for (int z = 0; z < n; z++){
                tmp[z] = *i;
                i += 1;
            }
            insert_rows(p, tmp);
        }
        return iterator((p-(il.end() - il.begin())).iter);
    }

    /*!
     * @brief Вставка в матрицу строк элементов из спска инициалазации
     * @param p Константный итератор, перед которым будут вставлены строки
     * @param il Список инициализации
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_rows(const_iterator p, std::initializer_list<T> il) requires std::move_constructible<T> {
        if (n == 0){
            n = il.end() - il.begin();
        }

        if(il.end() == il.begin() || (il.end() - il.begin()) % n != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        for(auto i = il.begin(); i != il.end();){
            valuetype *tmp = new valuetype[n];
            for (int z = 0; z < n; z++){
                tmp[z] = *i;
                i += 1;
            }
            insert_rows(p, tmp);
        }
        return iterator((p-(il.end() - il.begin())).iter);
    }
    /*!
     * @brief Вставка в матрицу столбцов элементов из спска инициалазации
     * @param p Итератор, перед которым будут вставлены столбцы
     * @param il Список инициализации
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_cols(iterator p, std::initializer_list<T> il) requires std::move_constructible<T> {
        if (m == 0){
            n = il.end() - il.begin();
        }
        if(il.end() == il.begin() || (il.end() - il.begin()) % m != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        for(auto i = il.begin(); i != il.end();){
            valuetype *tmp = new valuetype[m];
            for (int z = 0; z < m; z++){
                tmp[z] = *i;
                i += 1;
            }
            insert_cols(p, tmp);
        }
        return iterator((p-(il.end() - il.begin())/m).iter);
    }
    /*!
     * @brief Вставка в матрицу столбцов элементов из спска инициалазации
     * @param p Константный итератор, перед которым будут вставлены столбцы
     * @param il Список инициализации
     * @returns Итератор на последний вставленный элемент
     */
    iterator insert_cols(const_iterator p, std::initializer_list<T> il) requires std::move_constructible<T> {
        if (m == 0){
            n = il.end() - il.begin();
        }
        if(il.end() == il.begin() || (il.end() - il.begin()) % m != 0) {
            return iterator(const_cast<valuetype*>(p.iter));
        }

        for(auto i = il.begin(); i != il.end();){
            valuetype *tmp = new valuetype[m];
            for (int z = 0; z < m; z++){
                tmp[z] = *i;
                i += 1;
            }
            insert_cols(p, tmp);
        }
        std::cout<<p-(il.end() - il.begin())/m;
        return iterator((p-(il.end() - il.begin())/m).iter);
    }
    /*!
     * @brief Удаление строки из матрицы
     * @param q Итератор, адресующий строку для удаления
     * @returns Итератор на строку, находившуюся сразу после удаленной
     */
    iterator erase_rows(iterator q) noexcept{
        iterator next = q;
        if ((q - begin()) % n == 0 && q != end()){
            next += n;
            erase_row((q - begin()) / n);
        }
        return next;
    }
    /*!
     * @brief Удаление строки из матрицы
     * @param q Константный итератор, адресующий строку для удаления
     * @returns Итератор на строку, находившуюся сразу после удаленной
     */
    iterator erase_rows(const_iterator q) noexcept{
        iterator next = iterator(const_cast<valuetype*>(q.iter));
        if ((q - begin()) % n == 0 && q != end()){
            next += n;
            erase_row((*q.iter - *begin().iter) / n);
        }
        return next;
    }
    /*!
     * @brief Удаление столбца из матрицы
     * @param q Итератор, адресующий столбец для удаления
     * @returns Итератор на столбец, находившийся сразу после удаленного
     */
    iterator erase_cols(iterator q) noexcept {
        iterator next = q;
        if (q - begin() < n && q != end()){
            erase_col(q -begin());
            next += 1;
            return next;
        }
        return next;
    }
    /*!
     * @brief Удаление столбца из матрицы
     * @param q Константный итератор, адресующий столбец для удаления
     * @returns Итератор на столбец, находившийся сразу после удаленного
     */
    iterator erase_cols(const_iterator q) noexcept {
        iterator next = iterator(const_cast<valuetype*>(q.iter));
        if (q - begin() < n && q != end()){
            next = iterator(const_cast<valuetype*>((q+1).iter));
            erase_col(q -begin());
            return next;
        }
        return next;
    }
    /*!
     * @brief Удаление строк из матрицы в диапазоне [q1, q2)
     * @param q1 Начало диапазона
     * @param q2 Конец диапазона
     * @returns Итератор на строку, находившуюся сразу после последней удаленной
     */
    iterator erase_rows(iterator q1, iterator q2) noexcept {
        for (int i = 0; i < q2 - q1; i++){
            erase_rows(q1);
        }
        return q2;
    }
    /*!
     * @brief Удаление строк из матрицы в диапазоне [q1, q2)
     * @param q1 Константное начало диапазона
     * @param q2 Константный конец диапазона
     * @returns Итератор на строку, находившуюся сразу после последней удаленной
     */
    iterator erase_rows(const_iterator q1, const_iterator q2) noexcept {
        for (int i = 0; i < q2 - q1; i++){
            erase_rows(q1);
        }
        return q2;
    }
    /*!
     * @brief Удаление столбцов из матрицы в диапазоне [q1, q2)
     * @param q1 Начало диапазона
     * @param q2 Конец диапазона
     * @returns Итератор на столбец, находившийся сразу после последнего удаленного
     */
    iterator erase_cols(iterator q1, iterator q2) noexcept {
        for (int i = 0; i < q2 - q1; i++){
            erase_cols(q1);
        }
        return q2;
    }
    /*!
     * @brief Удаление столбцов из матрицы в диапазоне [q1, q2)
     * @param q1 Константное начало диапазона
     * @param q2 Константный конец диапазона
     * @returns Итератор на столбец, находившийся сразу после последнего удаленного
     */
    iterator erase_cols(const_iterator q1, const_iterator q2) noexcept {
        for (int i = 0; i < q2 - q1; i++){
            erase_cols(q1);
        }
        return q2;
    }
    /*!
     * @brief Удаление всех элементов из списка
     */
    void clear() noexcept{
        erase_rows(begin(), end());
    }
    /*!
     * @brief Замена значенийатрицы на строки из диапазона [i, j)
     * @param i Начало диапазона
     * @param j Конец диапазона
     */
    template<std::forward_iterator It>
    void assign(It i, It j) requires std::copy_constructible<T> {
        clear();
        insert_rows(end(), i, j);
    }
    /*!
     * @brief Замена значений матрицы на строки из списка инициализации
     * @param il Список инициализации для вставки
     */
    template<std::forward_iterator It>
    void assign(std::initializer_list<T> il) requires std::copy_constructible<T>{
        clear();
        insert_rows(end(), std::move(il));
    }
    /*!
     * @brief Замена значений матрицы на n копий строк t
     * @param n Количество строк для вставки
     * @param t Строка для вставки
     */
    template<std::forward_iterator It>
    void assign(size_type n, const valuetype& t) requires std::copy_constructible<T>{
        clear();
        insert_rows(end(), n, t);
    }


    /*!
     * @brief Получение спецаильного итератора на начало матрицы
     * @returns Специальный итератор, адресующий начало матрицы
     */
    SpecialIterator beginS(std::function<bool(Cell С, int i)> F) noexcept {
        return SpecialIterator(*this, 0, F);
    }
    /*!
     * @brief Получение спецаильного итератора на конец матрицы
     * @returns Специальный итератор, адресующий конец матрицы
     */
    SpecialIterator endS() noexcept {
        return SpecialIterator(*this, m * n);
    }
    /*!
     * @brief Получение итератора на начало матрицы
     * @returns Итератор, адресующий начало матрицы
     */
    iterator begin() noexcept {
        return iterator(matrix);
    }
    /*!
     * @brief Получение итератора на конец матрицы
     * @returns Мтератор, адресующий конец матрицы
     */
    iterator end() noexcept {
        return iterator(matrix + m * n);
    }
    /*!
     * @brief Получение константного итератора на начало матрицы
     * @returns Константный итератор, адресующий начало матрицы
     */
    const_iterator begin() const noexcept {
        return const_iterator(matrix);
    }
    /*!
     * @brief Получение константного итератора на начало матрицы
     * @returns Константный итератор, адресующий начало матрицы
     */
    const_iterator end() const noexcept {
        return const_iterator(matrix + m * n);
    }
    /*!
     * @brief Получение константного итератора на начало матрицы
     * @returns Константный итератор, адресующий начало матрицы
     */
    const_iterator cbegin() const noexcept {
        return const_iterator(matrix);
    }
    /*!
     * @brief Получение константного итератора на начало матрицы
     * @returns Константный итератор, адресующий начало матрицы
     */
    const_iterator cend() const noexcept {
        return const_iterator(matrix + m * n);
    }

    /*!
     * @brief Обменивает состояния двух матриц между собой
     * @param M Матрица для обмена состоянием
     */
    void swap(Matrix &M) noexcept {
        std::swap(m, M.m);
        std::swap(n, M.n);
        std::swap(matrix, M.matrix);
    }
    /*!
     * @brief Получение размера матрицы
     * @return Размер матрицы
     */
    size_type size() const noexcept {
        return m * n;
    }
    /*!
     * @brief Получение максимального размера матрицы
     * @return Максимальньый размер матрицы
     */
    size_type maxSize() const noexcept {
        return max_size;
    }
    /*!
     * @brief Проверка на пустоту матрицы
     * @return bool Пустота матрицы
     */
    bool empty() const noexcept{
        return m * n == 0;
    }



};



#endif // MATRIX_H
