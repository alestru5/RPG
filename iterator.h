#include <iostream>
#include <concepts>
#include <type_traits>
#include <functional>

template <typename T1, bool isConst>
class Iterator{
    public:
        typedef std::ptrdiff_t difference_type;
        typedef T1 value_type;
        typedef std::conditional_t<isConst, const T1, T1>* pointer;
        typedef std::conditional_t<isConst, const T1, T1>& reference;
        typedef std::contiguous_iterator_tag iterator_category;
        
        T1 iter;
        
        friend Iterator<T1, !isConst>;

        Iterator() noexcept: iter(T1()) {}
        explicit Iterator(const T1 &element) noexcept: iter(element) {}
        
        template<bool otherConst>
        explicit Iterator(const Iterator <T1, otherConst> &I) noexcept requires (isConst >= otherConst): iter(I.iter) {}
        
        template<bool otherConst>
        explicit Iterator(const Iterator <T1, otherConst> &&I) noexcept requires (isConst >= otherConst): iter(I.iter){
            I.iter = nullptr;
        }
        
        template<bool otherConst>
        Iterator& operator =(const Iterator<T1, otherConst>& I) noexcept requires (isConst >= otherConst) {
            if (*this != I){
                iter = I.iter;
            }
            return *this;
        }
        
        template<bool otherConst>
        Iterator& operator =(const Iterator<T1, otherConst>&& I) noexcept requires (isConst >= otherConst) {
            if (this != &I){
                iter = I.iter;
                I.iter = nullptr;
            }
            return *this;
        }
        
        Iterator& operator ++() noexcept {
            ++iter;
            return *this;
        }
        
        Iterator operator ++(int) noexcept {
            Iterator tmp(iter);
            iter++;
            return tmp;
        }
        
        Iterator& operator --() noexcept {
            --iter;
            return *this;
        }
        
        Iterator operator --(int) noexcept {
            Iterator tmp(iter);
            iter--;
            return tmp;
        }
        
        Iterator& operator +=(difference_type n) noexcept{
            iter += n;
            return *this;
        }
        
        Iterator& operator -=(difference_type n) noexcept{
            iter -= n;
            return *this;
        }
        
        Iterator operator +(difference_type n) const noexcept {
            return Iterator(iter + n);
        }
        
        Iterator operator -(difference_type n) const noexcept {
            return Iterator(iter - n);
        }
        
        reference operator *() noexcept{
            return iter;
        }
        
        std::add_const_t<reference> operator *() const noexcept {
            return iter;
        }
        
        pointer operator ->() const noexcept;
    
        
        reference operator[](difference_type n) const noexcept {
            return iter[n];
        }
        
        const T1 &Base() const noexcept {
            return iter;
        }
};
    
template<typename T1, bool isConst, bool otherConst>
bool operator <(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() < rhs.Base();
}

template<typename T1, bool isConst, bool otherConst>
bool operator >(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() > rhs.Base();
}

template<typename T1, bool isConst, bool otherConst>
bool operator <=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() <= rhs.Base();
}

template<typename T1, bool isConst, bool otherConst>
bool operator >=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() >= rhs.Base();
}
template<typename T1, bool isConst, bool otherConst>
bool operator ==(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() == rhs.Base();
}

template<typename T1, bool isConst, bool otherConst>
bool operator !=(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() != rhs.Base();
}

template<typename T1, bool isConst, bool otherConst>
std::ptrdiff_t operator -(const Iterator<T1, isConst>& lhs, const Iterator<T1, otherConst>& rhs){
    return lhs.Base() - rhs.Base();
}

template<typename T1, bool isConst>
Iterator<T1, isConst> operator +(std::ptrdiff_t n, const Iterator<T1, isConst> &rhs){
    return Iterator(n + rhs.Base());
}

