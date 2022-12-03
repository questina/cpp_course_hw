#ifndef CPP_COURSE_HW_MATRIX_H
#define CPP_COURSE_HW_MATRIX_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include "Vector.hpp"

template <typename T, size_t M, size_t N>
class Matrix{
private:
    template <size_t P>
    T determinant_one_step(Matrix<T, P, P>, unsigned int) const;
    T co_factor(Matrix<T, M, N>, int, int, int) const;
    Matrix<T, M, N> adjoint_matr(Matrix<T, M, N>, int) const;
public:
    T array[M][N];

    // constructors
    explicit Matrix();
    Matrix(const Matrix<T, M, N>&);
    explicit Matrix(const T&);
    Matrix(Vector<T, M, N>&);
    Matrix(T[M][N]);

    // get elem from index
    T& operator()(unsigned int, unsigned int);

    // get row
    Vector<T, 1, N> get_row(unsigned int) const;
    // get col
    Vector<T, M, 1> get_col(unsigned int) const;

    // operators between matrices
    Matrix<T, M, N>  operator+ (const Matrix<T, M, N>&) const;
    Matrix<T, M, N>& operator+=(const Matrix<T, M, N> &);
    Matrix<T, M, N>  operator- (const Matrix<T, M, N>&) const;
    Matrix<T, M, N>& operator-=(const Matrix<T, M, N> &);

    Matrix<T, M, N> operator* (const Matrix<T, M, N>&) const;
    Matrix<T, M, N>& operator*= (const Matrix<T, M, N>&);

    // operators with number
    Matrix<T, M, N> operator+ (const T&) const;
    Matrix<T, M, N>& operator += (const T&);
    Matrix<T, M, N> operator- (const T&) const;
    Matrix<T, M, N>& operator-= (const T&);
    Matrix<T, M, N>  operator* (const T&) const;
    Matrix<T, M, N>& operator*=(const T&);

    // operators with vectors
    template<size_t Q>
    Matrix<T, M, Q> dot (Vector<T, N, Q>&) const;
    template<size_t P, size_t Q>
    Matrix<T, M, N> mult (Vector<T, P, Q>&, unsigned int) const;
    template<size_t P, size_t Q>
    Matrix<T, M, N>  add (Vector<T, P, Q>&, unsigned int) const;
    template<size_t P, size_t Q>
    Matrix<T, M, N>  sub (Vector<T, P, Q>&, unsigned int) const;

    // operators with matrix
    template<size_t Q>
    Matrix<T, M, Q> dot (const Matrix<T, N, Q>&) const;

    Matrix<T, N, M> transpose() const;
    T determinant() const;
    Matrix<T, M, N> inverse() const;
    Vector<T, 1, M> diagonal() const;

    template<size_t i1, size_t i2, size_t j1, size_t j2, size_t I = i2 - i1, size_t J = j2 - j1>
            Matrix<T, I, J> slice();

};

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = 0;
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
            array[i][j] = num;
        }
    }
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(T arr[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = arr[i][j];
        }
    }
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N>::Matrix(Vector<T, M, N> &v) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = N == 1 ? v(i) : v(j);
        }
    }
}

template<typename T, size_t M, size_t N>
T &Matrix<T, M, N>::operator()(unsigned int row, unsigned int col){
    return array[row][col];
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix<T, M, N> &mat) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] + mat.array[i][j];
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const Matrix<T, M, N>&mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] += mat.array[i][j];
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix<T, M, N> & mat) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] - mat.array[i][j];
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const Matrix<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] -= mat.array[i][j];
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator*(const Matrix<T, M, N> & mat) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] * mat.array[i][j];
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator*=(const Matrix<T, M, N> &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] *= mat.array[i][j];
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator*(const T &num) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] * num;
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator*=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] *= num;
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator+(const T & num) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] + num;
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] += num;
        }
    }
    return *this;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const T & num) const {
    Matrix<T, M, N> res;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            res.array[i][j] = this->array[i][j] - num;
        }
    }
    return res;
}

template< typename T, size_t M, size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const T &num) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->array[i][j] -= num;
        }
    }
    return *this;
}

template<typename T, size_t M, size_t N>
Matrix<T, N, M> Matrix<T, M, N>::transpose() const {
    Matrix<T, N, M> res;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            res.array[i][j] = this->array[j][i];
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
Vector<T, 1, M> Matrix<T, M, N>::diagonal() const {
    Vector<T, 1, M> res;
    for (int i = 0; i < M; i++) {
        res.array[0][i] = this->array[i][i];
    }
    return res;
}

template< typename T, size_t M, size_t N>
Vector<T, M, 1> Matrix<T, M, N>::get_col(unsigned int col_idx) const {
    Vector<T, M, 1> res;
    for (int i = 0; i < M; i++){
        res.array[i][0] = this->array[i][col_idx];
    }
    return res;
}

template< typename T, size_t M, size_t N>
Vector<T, 1, N> Matrix<T, M, N>::get_row(unsigned int row_idx) const {
    Vector<T, 1, N> res;
    for (int j = 0; j < N; j++){
        res.array[0][j] = this->array[row_idx][j];
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t Q>
Matrix<T, M, Q> Matrix<T, M, N>::dot(Vector<T, N, Q> &v) const {
    Matrix<T, M, Q> res;
    int cur_sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            cur_sum = 0;
            for (int k = 0; k < N; k++){
                cur_sum += this->array[i][k] * v.array[k][j];
            }
            res.array[i][j] = cur_sum;
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t Q>
Matrix<T, M, Q> Matrix<T, M, N>::dot(const Matrix<T, N, Q> &matr) const {
    Matrix<T, M, Q> res;
    int cur_sum;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            cur_sum = 0;
            for (int k = 0; k < N; k++){
                cur_sum += this->array[i][k] * matr.array[k][j];
            }
            res.array[i][j] = cur_sum;
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, size_t Q>
Matrix<T, M, N> Matrix<T, M, N>::add(Vector<T, P, Q> &v, const unsigned int axis) const {
    // TODO axis < 0 > 2
    static_assert((M == N == P) || (M == N == Q) || (M == P != 1) || (N == Q != 1), "Incorrect matrix and vector dimensions");
    Matrix<T, M, N> res;
    if ((M == N == P) || (M == N == Q)) {
        if (axis == 0) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] + v(i);
                }
            }
        } else {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] + v(j);
                }
            }
        }
    } else {
        if (M == P != 1) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] + v(i);
                }
            }
        } else {
            if (N == Q != 1) {
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        res.array[i][j] = this->array[i][j] + v(j);
                    }
                }
            }
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, size_t Q>
Matrix<T, M, N> Matrix<T, M, N>::sub(Vector<T, P, Q> &v, const unsigned int axis) const {
    // TODO axis < 0 > 2
    static_assert((M == N == P) || (M == N == Q) || (M == P != 1) || (N == Q != 1), "Incorrect matrix and vector dimensions");
    Matrix<T, M, N> res;
    if ((M == N == P) || (M == N == Q)) {
        if (axis == 0) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] - v(i);
                }
            }
        } else {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] - v(j);
                }
            }
        }
    } else {
        if (M == P != 1) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] - v(i);
                }
            }
        } else {
            if (N == Q != 1) {
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        res.array[i][j] = this->array[i][j] - v(j);
                    }
                }
            }
        }
    }
    return res;
}

template<typename T, size_t M, size_t N>
template<size_t P, size_t Q>
Matrix<T, M, N> Matrix<T, M, N>::mult(Vector<T, P, Q> &v, const unsigned int axis) const {
    static_assert((M == N == P) || (M == N == Q) || (M == P != 1) || (N == Q != 1), "Incorrect matrix and vector dimensions");
    Matrix<T, M, N> res;
    if ((M == N == P) || (M == N == Q)) {
        if (axis == 0) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] * v(i);
                }
            }
        } else {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] * v(j);
                }
            }
        }
    } else {
        if (M == P != 1) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    res.array[i][j] = this->array[i][j] * v(i);
                }
            }
        } else {
            if (N == Q != 1) {
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        res.array[i][j] = this->array[i][j] * v(j);
                    }
                }
            }
        }
    }
    return res;
}


template<typename T, size_t M, size_t N>
T Matrix<T, M, N>::determinant() const{
    static_assert(M == N, "To calculate determinant matrix must be squared");
    T det = determinant_one_step(*this, M);
    return det;
}

template<typename T, size_t M, size_t N>
template<size_t P>
T Matrix<T, M, N>::determinant_one_step(Matrix<T, P, P> matr, unsigned int size) const{
    if (size == 2) {
        return ((matr.array[0][0] * matr.array[1][1]) - (matr.array[1][0] * matr.array[0][1]));
    }
    if (size == 1) {
        return matr.array[0][0];
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
                submatr.array[subi][subj] = matr.array[j][k];
                subj++;
            }
            subi++;
        }
        det = det + (pow(-1, i) * matr.array[0][i] * this->determinant_one_step(submatr, size - 1));
    }
    return det;
}

template<typename T, size_t M, size_t N>
T Matrix<T, M, N>::co_factor(Matrix<T, M, N> mat, int n, int j, int i) const{
    T fac = 0;
    Matrix<T, M - 1, M - 1> mat_red;
    int i_m = 0;
    for (int r = 0; r < n; r++) {
        int j_m = 0;
        if (r != i) {
            for (int c = 0; c < n; c++) {
                if (c != j) {
                    mat_red.array[i_m][j_m] = mat.array[r][c];
                    j_m++;
                }
            }
            i_m++;
        }
    }
    fac = pow(-1, i + j + 2) * this->determinant_one_step(mat_red, n - 1);
    return fac;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::adjoint_matr(Matrix<T, M, N> mat, int n) const{
    Matrix<T, M, N> adj_matr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            adj_matr.array[i][j] = this->co_factor(mat, n, i, j);
        }
    }
    return adj_matr;
}

template<typename T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T, M, N>::inverse() const {
    Matrix<T, M, N> inv_matr;
    T det = this->determinant();
    if (det != 0) {
        Matrix<T, M, N> adj_matr = adjoint_matr(*this, M);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                inv_matr.array[i][j] = 1.0 / det * adj_matr.array[i][j];
            }
        }
    }
    return inv_matr;
}

#endif //CPP_COURSE_HW_MATRIX_H
