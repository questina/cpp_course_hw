#ifndef CPP_COURSE_HW_VECTOR_H
#define CPP_COURSE_HW_VECTOR_H

#include <cstdio>
#include <type_traits>


template<typename T, size_t M, size_t N = 1>
class Vector {
public:
    T array[M][N];
    explicit Vector();
    Vector(const Vector<T, M, N>&);
    explicit Vector(const T&);
    explicit Vector(T[M][N]);

    T& operator()(unsigned int);

    Vector<T, M, N>  operator+ (const Vector<T, M, N>&) const;
    Vector<T, M, N>& operator+=(const Vector<T, M, N>&);
    Vector<T, M, N>  operator- (const Vector<T, M, N>&) const;
    Vector<T, M, N>& operator-=(const Vector<T, M, N>&);

    Vector<T, M, N> operator* (const Vector<T, M, N>&) const;
    Vector<T, M, N>& operator*= (const Vector<T, M, N>&);

    //operators with number
    Vector<T, M, N>  operator* (const T&) const;
    Vector<T, M, N>& operator*=(const T&);
    Vector<T, M, N>  operator+ (const T&) const;
    Vector<T, M, N>& operator+=(const T&);
    Vector<T, M, N>  operator- (const T&) const;
    Vector<T, M, N>& operator-=(const T&);

};

template<typename T, size_t M, size_t N>
Vector<T, M, N>::Vector() {
    static_assert(M == 1 || N == 1, "One of the axis must be equal to one.");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = 0;
        }
    }
}

template<typename T, size_t M, size_t N>
Vector<T, M, N>::Vector(const Vector<T, M, N> &source) {
    (*this) = source;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N>::Vector(const T &num) {
    static_assert(M == 1 || N == 1, "One of the axis must be equal to one.");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = num;
        }
    }
}

template<typename T, size_t M, size_t N>
Vector<T, M, N>::Vector(T vect[M][N]) {
    static_assert(M == 1 || N == 1, "One of the axis must be equal to one.");
    if (M == 1) {
        for (int j = 0; j < N; j++) {
            array[0][j] = vect[0][j];
        }
    } else {
        for (int i = 0; i < M; i++) {
            array[i][0] = vect[i][0];
        }
    }
}

template<typename T, size_t M, size_t N>
T &Vector<T, M, N>::operator()(unsigned int idx) {
    if (M == 1) {
        return array[0][idx];
    } else {
        return array[idx][0];
    }
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator+(const Vector<T, M, N> &mat) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] + mat.array[i][j];
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N>& Vector<T, M, N>::operator+=(const Vector<T, M, N>&mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] += mat.array[i][j];
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator-(const Vector<T, M, N> & mat) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] - mat.array[i][j];
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N>& Vector<T, M, N>::operator-=(const Vector<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] -= mat.array[i][j];
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator*(const Vector<T, M, N> & mat) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] * mat.array[i][j];
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> &Vector<T, M, N>::operator*=(const Vector<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] *= mat.array[i][j];
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator*(const T &num) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] * num;
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> &Vector<T, M, N>::operator*=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] *= num;
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator+(const T &num) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] + num;
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> &Vector<T, M, N>::operator+=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] += num;
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> Vector<T, M, N>::operator-(const T &num) const {
    Vector<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] - num;
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, M, N> &Vector<T, M, N>::operator-=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] -= num;
        }
    }
    return *this;
}


#endif //CPP_COURSE_HW_VECTOR_H
