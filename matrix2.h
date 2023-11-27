#include <iostream>
#include <concepts>
#include <type_traits>
#include <limits>

#include "iterator.h"

template <typename T>
class Matrix2{
    typedef std::allocator_traits<std::allocator<T>>::value_type valuetype;
    typedef std::allocator_traits<std::allocator<T>>::pointer pointer;
    typedef std::allocator_traits<std::allocator<T>>::const_pointer const_pointer;
    typedef valuetype& reference;
    typedef const valuetype& const_reference;
    typedef Iterator<pointer, false> iterator;    
    typedef Iterator<pointer, true> const_iterator;
    typedef std::ptrdiff_t different_type;
    typedef std::allocator_traits<std::allocator<T>>::size_type size_type;

    public:
        int max_size;
        int m;
        int n;
        pointer matrix = nullptr;

    public:
        Matrix2() noexcept (std::is_nothrow_default_constructible_v<T>): m(0), n(0), max_size(100 * 100), matrix(new valuetype[max_size]) {}
        Matrix2(const Matrix2 &M) requires std::copy_constructible<T>: Matrix2() {
            m = M.m;
            n = M.n;
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    matrix[i * n + j] = M.matrix[i * n + j];
                }
            }
        }
        Matrix2(const int i, const int j, valuetype val) noexcept: Matrix2(){
            if (i > 0 && j > 0 && i * j < max_size){
                m = i;
                n = j;
                for (int k = 0; k < m * n; k++){
                    matrix[k] = val;  
                }
            }
        }
        Matrix2(Matrix2 &&M) requires std::copy_constructible<T>: Matrix2() {
            swap(M);
        }
        Matrix2(size_type n, const pointer&t) requires std::copy_constructible<T>: Matrix2() {
            insert_rows(end(), n, t);
        }
        template<std::input_iterator It>
        Matrix2(It i, It j) requires std::constructible_from<pointer, std::iter_reference_t<It>>: Matrix2(){
            insert_rows(end(), i, j);
        }
        Matrix2(std::initializer_list<T> il) requires std::move_constructible<T>: Matrix2(){
            insert_rows(end(), std::move(il));
        }
        ~Matrix2() {
            clear();
        }

        pointer allocate(pointer P){
            return P;
        }

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


        int getM() const noexcept { return m; }
        int getN() const noexcept { return n; }
        T* getMatrix() noexcept { return matrix; } 
        
        Matrix2& operator = (const Matrix2& o) requires std::copy_constructible<T> {
            if (this == &o){
                return *this;
            }
            assign(o.cbegin(), o.cend());
            return *this;
        }
        Matrix2& operator = (Matrix2&& o) noexcept {
            swap(o);
            return *this;
        }
        Matrix2& operator = (std::initializer_list<T> il) requires std::move_constructible<T>{
            assign(std::move(il));
            return *this;
        }

        valuetype* operator[] (int index){
            return &matrix[index/n + index%n];
        }
        
        template<typename ...Args>
        iterator emplace_rows(iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
            
            if((p -begin()) % n != 0) {
                
                return iterator(const_cast<valuetype*>(p.iter));
            }
            pointer tmp = allocate(args...);
            
            insert_row((p -begin()) / n, tmp);
            return iterator(tmp);
        }

        template<typename ...Args>
        iterator emplace_rows(const_iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
            
            if((p - begin()) % n != 0) {
                return iterator(const_cast<valuetype*>(p.iter));
            }
            pointer tmp = allocate(args...);
            insert_row((p - begin()) / n, tmp);
            return iterator(tmp);
        }

        template<typename ...Args>
        iterator emplace_cols(iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
            if(p - begin() > n) {
                return iterator(const_cast<valuetype*>(p.iter));
            }
            
            pointer tmp = allocate(args...);
            insert_col(p -begin(), tmp);
            return iterator(tmp);
        }

        template<typename ...Args>
        iterator emplace_cols(const_iterator p, Args && ... args) requires std::constructible_from<pointer, Args...>{
            if(p -begin() > n) {
                return iterator(const_cast<valuetype*>(p.iter));
            }
            pointer tmp = allocate(args...);
            insert_col(p - begin(), tmp);
            return iterator(tmp);
        }

        iterator insert_rows(iterator p, const pointer& t) requires std::copy_constructible<T>{
            return emplace_rows(p, t);
        }

        iterator insert_rows(const_iterator& p, const pointer& t) requires std::copy_constructible<T>{
            return emplace_rows(p, t);
        }

        iterator insert_cols(iterator p, const pointer& t) requires std::copy_constructible<T>{
            return emplace_cols(p, t);
        }

        iterator insert_cols(const_iterator p, const pointer& t) requires std::copy_constructible<T>{
            return emplace_cols(p, t);
        }

        iterator insert_rows(iterator p, pointer&& t) requires std::move_constructible<T> {
            return emplace_rows(p, std::move(t));
        }

        iterator insert_rows(const_iterator p, pointer&& t) requires std::move_constructible<T> {
            return emplace_rows(p, std::move(t));
        }

        iterator insert_cols(iterator p, pointer&& t) requires std::move_constructible<T> {
            return emplace_cols(p, std::move(t));
        }

        iterator insert_cols(const_iterator p, pointer&& t) requires std::move_constructible<T> {
            return emplace_cols(p, std::move(t));
        }

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

        iterator erase_rows(iterator q) noexcept{
            iterator next = q;
            if ((q - begin()) % n == 0 && q != end()){
                next += n;
                erase_row((q - begin()) / n);
            }
            return next; 
        }

        iterator erase_rows(const_iterator q) noexcept{
            iterator next = iterator(const_cast<valuetype*>(q.iter));
            if ((q - begin()) % n == 0 && q != end()){
                next += n;
                erase_row((*q.iter - *begin().iter) / n);
            }
            return next; 
        }

        iterator erase_cols(iterator q) noexcept {
            iterator next = q;
            if (q - begin() < n && q != end()){
                erase_col(q -begin());
                next += 1;
                return next;
            }
            return next; 
        }  

        iterator erase_cols(const_iterator q) noexcept {
            iterator next = iterator(const_cast<valuetype*>(q.iter));
            if (q - begin() < n && q != end()){
                next = iterator(const_cast<valuetype*>((q+1).iter));
                erase_col(q -begin());
                return next;
            }
            return next;  
        }   

        iterator erase_rows(iterator q1, iterator q2) noexcept {
            for (int i = 0; i < q2 - q1; i++){
                erase_rows(q1);
            }
            return q2;
        }

        iterator erase_rows(const_iterator q1, const_iterator q2) noexcept {
            for (int i = 0; i < q2 - q1; i++){
                erase_rows(q1);
            }
            return q2;
        }

        iterator erase_cols(iterator q1, iterator q2) noexcept {
            for (int i = 0; i < q2 - q1; i++){
                erase_cols(q1);
            }
            return q2;
        }

        iterator erase_cols(const_iterator q1, const_iterator q2) noexcept {
            for (int i = 0; i < q2 - q1; i++){
                erase_cols(q1);
            }
            return q2;
        }

        void clear() noexcept{
            erase_rows(begin(), end());
        }

        template<std::forward_iterator It>
        void assign(It i, It j) requires std::copy_constructible<T> {
            clear();
            insert_rows(end(), i, j);
        }

        template<std::forward_iterator It>
        void assign(std::initializer_list<T> il) requires std::copy_constructible<T>{
            clear();
            insert_rows(end(), std::move(il));
        }

        template<std::forward_iterator It>
        void assign(size_type n, const valuetype& t) requires std::copy_constructible<T>{
            clear();
            insert_rows(end(), n, t);
        }

        

       iterator begin() noexcept {
            return iterator(matrix);
        }

        iterator end() noexcept {
            return iterator(matrix + m * n);
        }

        const_iterator begin() const noexcept {
            return const_iterator(matrix);
        }

        const_iterator end() const noexcept {
            return const_iterator(matrix + m * n);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(matrix);
        }

        const_iterator cend() const noexcept {
            return const_iterator(matrix + m * n);
        }

        void swap(Matrix2 &M) noexcept {
            std::swap(m, M.m);
            std::swap(n, M.n);
            std::swap(matrix, M.matrix);
        }

        size_type size() const noexcept {
            return m * n;
        }

        size_type maxSize() const noexcept {
            return max_size;
        }

        bool empty() const noexcept{
            return m * n == 0;
        }

        
};

