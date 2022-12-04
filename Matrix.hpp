#ifndef CPP_COURSE_HW_MATRIX_H
#define CPP_COURSE_HW_MATRIX_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include "Vector.hpp"

template <typename T = double, size_t M = 0, size_t N = 0>
class Matrix{
private:
    T array[M*N];
    template <size_t P>
    T determinant_one_step(Matrix<T, P, P>, unsigned int) const;
    Matrix<T, M, 2*N> calc_inverse(Matrix<T, M, 2*N>) const;
public:

    // constructors
    explicit Matrix();
    Matrix(const Matrix<T, M, N>&);
    explicit Matrix(const T&);
    explicit Matrix(Vector<T, N>&);
    explicit Matrix(Vector<T, M, true>&);
    explicit Matrix(T[M][N]);


    // get elem from index
    T operator()(unsigned int, unsigned int) const;
    void assign(int, int, T);

    // get row
    Vector<T, N> get_row(unsigned int) const;
    // get col
    Vector<T, M, true> get_col(unsigned int) const;

    // operators between matrices
    Matrix<T, M, N>  operator+ (const Matrix<T, M, N>&) const;
    Matrix<T, M, N>& operator+=(const Matrix<T, M, N> &);
    Matrix<T, M, N>  operator- (const Matrix<T, M, N>&) const;
    Matrix<T, M, N>& operator-=(const Matrix<T, M, N> &);

    // operators with number
    Matrix<T, M, N> operator+ (const T&) const;
    Matrix<T, M, N>& operator += (const T&);
    Matrix<T, M, N> operator- (const T&) const;
    Matrix<T, M, N>& operator-= (const T&);
    Matrix<T, M, N> operator* (const T&) const;
    Matrix<T, M, N>& operator*=(const T&);

    // operators with vectors
    Matrix<T, M, 1> operator* (Vector<T, N> &v) const;
    template<size_t Q>
    Matrix<T, M, Q> operator* (Vector<T, Q, true>&) const;
    template<size_t P, bool COL>
    Matrix<T, M, N> mult (Vector<T, P, COL>&, unsigned int) const;
    template<size_t P, bool COL>
    Matrix<T, M, N>  add (Vector<T, P, COL>&, unsigned int) const;
    template<size_t P, bool COL>
    Matrix<T, M, N>  sub (Vector<T, P, COL>&, unsigned int) const;

    // operators with matrix
    template<size_t Q>
    Matrix<T, M, Q> operator* (const Matrix<T, N, Q>&) const;
    Matrix<T, M, N> mult (const Matrix<T, M, N>&) const;

    Matrix<T, N, M> transpose() const;
    T determinant() const;
    Matrix<T, M, N> inverse() const;
    template<size_t P = std::min(M, N)>
    Vector<T, P> diagonal() const;

};

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i*N + j] = 0;
        }
    }
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(const Matrix<T, M, N> & source) {
    (*this) = source;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i*N + j] = num;
        }
    }
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(T arr[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i*N + j] = arr[i][j];
        }
    }
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(Vector<T, N> &v) {
    static_assert((M == 1), "To use this constructor matrix first dim must be equal to 1");
    for (int j = 0; j < N; j++) {
        array[j] = v(j);
    }
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(Vector<T, M, true> &v) {
    static_assert((N == 1), "To use this constructor matrix second dim must be equal to 1");
    for (int i = 0; i < M; i++) {
        array[i*N] = v(i);
    }
}

template<typename T, size_t M, size_t N>
T Matrix<T, M, N>::operator()(unsigned int row, unsigned int col) const{
    return array[row*N + col];
}

template<typename T, size_t M, size_t N>
void Matrix<T, M, N>::assign(int row, int col, T elem) {
    if ((row < 0 ) || (row >= M) || (col < 0) || (col >= N)) {
        throw std::invalid_argument("Index out of range");
    }
    this->array[row*N + col] = elem;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const Matrix<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i*N + j] += mat(i, j);
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix<T, M, N> &mat) const {
    return Matrix<T, M, N>(*this) += mat;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix<T, M, N> & mat) const {
    return Matrix<T, M, N>(*this) -= mat;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const Matrix<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i*N + j] -= mat(i, j);
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::mult(const Matrix<T, M, N> & mat) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            res.assign(i, j, this->array[i*N+j] * mat(i, j));
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator*(const T &num) const {
    return Matrix<T, M, N>(*this) *= num;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator*=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i*N + j] *= num;
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator+(const T & num) const {
    return Matrix<T, M, N>(*this) += num;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i*N + j] += num;
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const T & num) const {
    return Matrix<T, M, N>(*this) -= num;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i*N + j] -= num;
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Matrix<T, N, M> Matrix<T, M, N>::transpose() const {
    Matrix<T, N, M> res;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            res.assign(i, j, this->array[j*N + i]);
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P>
Vector<T, P, false> Matrix<T, M, N>::diagonal() const {
    std::cout << P << std::endl;
    Vector<T, P> res;
    for (int i = 0; i < std::min(M, N); i++) {
        res.assign(i, this->array[i*N + i]);
    }
    return res;
}

template< typename T, size_t M, size_t N>
Vector<T, M, true> Matrix<T, M, N>::get_col(unsigned int col_idx) const {
    Vector<T, M, true> res;
    for (int i = 0; i < M; i++){
        res.assign(i, this->array[i*N+ col_idx]);
    }
    return res;
}

template< typename T, size_t M, size_t N>
Vector<T, N> Matrix<T, M, N>::get_row(unsigned int row_idx) const {
    Vector<T, N> res;
    for (int j = 0; j < N; j++){
        res.assign(j, this->array[row_idx*N + j]);
    }
    return res;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, 1> Matrix<T, M, N>::operator*(Vector<T, N> &v) const {
    Matrix<T, M, 1> res;
    int cur_sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 1; j++) {
            cur_sum = 0;
            for (int k = 0; k < N; k++){
                cur_sum += this->array[i*N + k] * v(k);
            }
            res.assign(i, j, cur_sum);
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t Q>
Matrix<T, M, Q> Matrix<T, M, N>::operator*(Vector<T, Q, true> &v) const {
    static_assert((N == 1), "Matrix and vector shapes can not be aligned");
    Matrix<T, M, Q> res;
    int cur_sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            cur_sum = 0;
            for (int k = 0; k < N; k++){
                cur_sum += this->array[i*N + k] * v(j);
            }
            res.assign(i, j, cur_sum);
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t Q>
Matrix<T, M, Q> Matrix<T, M, N>::operator* (const Matrix<T, N, Q> &matr) const {
    Matrix<T, M, Q> res;
    int cur_sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            cur_sum = 0;
            for (int k = 0; k < N; k++){
                cur_sum += this->array[i*N + k] * matr(k, j);
            }
            res.assign(i, j, cur_sum);
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, bool COL>
Matrix<T, M, N> Matrix<T, M, N>::add(Vector<T, P, COL> &v, const unsigned int axis) const {
    if ((axis != 0) && (axis != 1)){
        throw std::invalid_argument("invalid axis");
    }
    static_assert(((N == P) && (!COL)) || ((M == P) && (!COL)), "invalid shapes");
    Matrix<T, M, N> res;
    if (axis == 0) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] + v(i));
            }
        }
    } else {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] + v(j));
            }
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, bool COL>
Matrix<T, M, N> Matrix<T, M, N>::sub(Vector<T, P, COL> &v, const unsigned int axis) const {
    if ((axis != 0) && (axis != 1)){
        throw std::invalid_argument("invalid axis");
    }
    static_assert(((N == P) && (!COL)) || ((M == P) && (!COL)), "invalid shapes");
    Matrix<T, M, N> res;
    if (axis == 0) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] - v(i));
            }
        }
    } else {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] - v(j));
            }
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, bool COL>
Matrix<T, M, N> Matrix<T, M, N>::mult(Vector<T, P, COL> &v, const unsigned int axis) const {
    if ((axis != 0) && (axis != 1)){
        throw std::invalid_argument("invalid axis");
    }
    static_assert(((N == P) && (!COL)) || ((M == P) && (!COL)), "invalid shapes");
    Matrix<T, M, N> res;
    if (axis == 0) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] * v(i));
            }
        }
    } else {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                res.assign(i, j, this->array[i*N + j] * v(j));
            }
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
T Matrix<T, M, N>::determinant() const{
    static_assert(M == N, "To calculate determinant, matrix must be squared");
    T det = determinant_one_step(*this, M);
    return det;
}

template<typename T, size_t M, size_t N>
template<size_t P>
T Matrix<T, M, N>::determinant_one_step(Matrix<T, P, P> matr, unsigned int size) const{
    if (size == 2) {
        return ((matr(0, 0) * matr(1, 1)) - (matr(1, 0) * matr(0, 1)));
    }
    if (size == 1) {
        return matr(0, 0);
    }
    if (size <= 0) {
        return 0;
    }
    T det = 0;
    Matrix<T, P, P> submatr;
    for (int i = 0; i < size; i++) {
        int subi = 0;
        for (int j = 1; j < size; j++) {
            int subj = 0;
            for (int k = 0; k < size; k++) {
                if (k == i) continue;
                submatr.assign(subi, subj, matr(j, k));
                subj++;
            }
            subi++;
        }
        det = det + (pow(-1, i) * matr(0, i) * this->determinant_one_step(submatr, size - 1));
    }
    return det;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, 2*N> Matrix<T, M, N>::calc_inverse(Matrix<T, M, 2*N> mat) const {
    int size = M;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2 * size; j++) {
            if (j == (i + size)) {
                mat.assign(i, j, 1);
            }
        }
    }
    for (int i = size - 1; i > 0; i--) {
        if (mat(i - 1, 0) < mat(i, 0)) {
            T tmp[size];
            for (int j = 0; j < 2 * size; j++) {
                tmp[j] = mat(i, j);
                mat.assign(i, j, mat(i - 1, j));
                mat.assign(i - 1, j, tmp[j]);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j != i) {
                T tmp = mat(j, i) / mat(i, i);
                for (int k = 0; k < 2 * size; k++) {
                    mat.assign(j, k, mat(j, k) - mat(i, k) * tmp);
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        T tmp = mat(i, i);
        for (int j = 0; j < 2 * size; j++) {
            mat.assign(i, j, mat(i, j) / tmp);
        }
    }

    return mat;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::inverse() const {
    static_assert(M == N, "To calculate inverse matrix, matrix must be squared");
    Matrix<T, M, 2*N> inv_matr;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            inv_matr.assign(i, j, this->array[i*N + j]);
        }
    }
    inv_matr = calc_inverse(inv_matr);
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            res.assign(i, j, inv_matr(i, j + N));
        }
    }
    return res;
}

#endif //CPP_COURSE_HW_MATRIX_H
