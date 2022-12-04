#ifndef CPP_COURSE_HW_VECTOR_H
#define CPP_COURSE_HW_VECTOR_H

#include <cstdio>
#include <type_traits>


template<typename T = double, size_t M = 0, bool COL = false>
class Vector {
private:
    T array[M];
    bool row;
public:
    explicit Vector();
    Vector(const Vector<T, M, COL>&);
    explicit Vector(const T&);
    explicit Vector(T[M]);

    T& operator()(unsigned int);
    void assign(int, T);

    Vector<T, M, COL>  operator+ (const Vector<T, M, COL>&) const;
    Vector<T, M, COL>& operator+=(const Vector<T, M, COL>&);
    Vector<T, M, COL>  operator- (const Vector<T, M, COL>&) const;
    Vector<T, M, COL>& operator-=(const Vector<T, M, COL>&);

    Vector<T, M, COL> operator* (const Vector<T, M, COL>&) const;
    Vector<T, M, COL>& operator*= (const Vector<T, M, COL>&);

    //operators with number
    Vector<T, M, COL>  operator* (const T&) const;
    Vector<T, M, COL>& operator*=(const T&);
    Vector<T, M, COL>  operator+ (const T&) const;
    Vector<T, M, COL>& operator+=(const T&);
    Vector<T, M, COL>  operator- (const T&) const;
    Vector<T, M, COL>& operator-=(const T&);

};

template<typename T, size_t M, bool COL>
Vector<T, M, COL>::Vector() {
    row = COL;
    for (int i = 0; i < M; i++) {
        array[i] = 0;
    }
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL>::Vector(const Vector<T, M, COL> &source) {
    (*this) = source;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL>::Vector(const T &num) {
    row = COL;
    for (int i = 0; i < M; i++) {
        array[i] = num;
    }
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL>::Vector(T vect[M]) {
    row = COL;
    for (int i = 0; i < M; i++) {
        array[i] = vect[i];
    }
}

template<typename T, size_t M, bool COL>
T &Vector<T, M, COL>::operator()(unsigned int idx) {
    return array[idx];
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator+(const Vector<T, M, COL> &vect) const {
    return Vector<T, M, COL>(*this) += vect;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL>& Vector<T, M, COL>::operator+=(const Vector<T, M, COL>&vect) {
    for (int i = 0; i < M; i++) {
        this->array[i] += vect.array[i];
    }
    return *this;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator-(const Vector<T, M, COL> &vect) const {
    return Vector<T, M, COL>(*this) -= vect;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL>& Vector<T, M, COL>::operator-=(const Vector<T, M, COL> &vect) {
    for (int i = 0; i < M; i++) {
        this->array[i] -= vect.array[i];
    }
    return *this;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator*(const Vector<T, M, COL> &vect) const {
    return Vector<T, M, COL>(*this) *= vect;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> &Vector<T, M, COL>::operator*=(const Vector<T, M, COL> &vect) {
    for (int i = 0; i < M; i++) {
        this->array[i] *= vect.array[i];
    }
    return *this;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator*(const T &num) const {
    return Vector<T, M, COL>(*this) *= num;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> &Vector<T, M, COL>::operator*=(const T &num) {
    for (int i = 0; i < M; i++) {
        this->array[i] *= num;
    }
    return *this;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator+(const T &num) const {
    return Vector<T, M, COL>(*this) += num;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> &Vector<T, M, COL>::operator+=(const T &num) {
    for (int i = 0; i < M; i++) {
        this->array[i] += num;
    }
    return *this;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> Vector<T, M, COL>::operator-(const T &num) const {
    return Vector<T, M, COL>(*this) -= num;
}

template<typename T, size_t M, bool COL>
Vector<T, M, COL> &Vector<T, M, COL>::operator-=(const T &num) {
    for (int i = 0; i < M; i++) {
        this->array[i] -= num;
    }
    return *this;
}

template<typename T, size_t M, bool COL>
void Vector<T, M, COL>::assign(int idx, T elem) {
    if ((idx < 0 ) || (idx >= M)) {
        throw std::invalid_argument("Index out of range");
    }
    this->array[idx] = elem;
}


#endif //CPP_COURSE_HW_VECTOR_H
