#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>

template <typename T, size_t M, bool COL>
bool equal(Vector<T, M, COL> v1, T v2[M]) {
    for (int i = 0; i < M; i++) {
        if (v1(i) != v2[i]) {
            std::cout << v1(i) << " " << v2[i] << std::endl;
            return false;
        }
    }
    return true;
}

template <typename T, size_t M, size_t N>
bool equal(Matrix<T, M, N> matr1, T matr2[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (matr1(i, j) != matr2[i][j]) {
                std::cout << matr1(i, j) << " " << matr2[i][j] << std::endl;
                return false;
            }
        }
    }
    return true;
}

int main(){
    Vector<int, 3> v1;
    int ans_v1[3] = {0, 0, 0};
    std::cout << equal(v1, ans_v1) << std::endl;
    float ans_v2[3] = {1.5, 2.7, 3.2};
    Vector<float, 3, true> v2(ans_v2);
    std::cout << equal(v2, ans_v2) << std::endl;
    Vector a;
    std::cout << a(0) << std::endl;
    double matr[3][3] = {{5, 7, 9}, {4, 3, 8}, {7, 5, 6}};
    Matrix<double, 3, 3> m(matr);
    m.inverse();
    return 0;
}