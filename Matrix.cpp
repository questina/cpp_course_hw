#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>

template <typename T, size_t M, size_t N>
bool equal(Vector<T, M, N> v1, T v2[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (v1(std::max(i, j)) != v2[i][j]) {
                std::cout << v1(std::max(i, j)) << " " << v2[i][j] << std::endl;
                return false;
            }
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
    Vector<int, 3, 1> v1;
    int ans_v1[3][1] = {0, 0, 0};
    std::cout << equal(v1, ans_v1) << std::endl;
    float ans_v2[1][3] = {1.5, 2.7, 3.2};
    Vector<float, 1, 3> v2(ans_v2);
    std::cout << equal(v2, ans_v2) << std::endl;
    return 0;
}