#include <gtest/gtest.h>
#include "../Matrix.hpp"
#include <iostream>

#define EPSILON 0.001

template <typename T, size_t M, size_t N>
bool equal(Matrix<T, M, N> matr1, T matr2[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(matr1(i, j) - matr2[i][j]) > EPSILON) {
                std::cout << i << " " << j << std::endl;
                std::cout << matr1(i, j) << " " << matr2[i][j] << std::endl;
                return false;
            }
        }
    }
    return true;
}

template <typename T, size_t M, bool COL>
bool equal(Vector<T, M, COL> v1, T v2[M]) {
    for (int i = 0; i < M; i++) {
        if (fabs(v1(i) - v2[i]) > EPSILON) {
            std::cout << v1(i) << " " << v2[i] << std::endl;
            return false;
        }
    }
    return true;
}

TEST(MatrixTest, TestConstructors) {
    // Test constructors of class Matrix
    Matrix<int, 3, 4> m1;
    int ans_m1[3][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    EXPECT_TRUE(equal(m1, ans_m1));
    float ans_m2[3][4] = {{1.5, 2.7, 3.2, 4.1}, {1.3, 3.8, 5.75, 7.3}, {2.5, 4.12, 6.111, 8.9}};
    Matrix<float, 3, 4> m2(ans_m2);
    EXPECT_TRUE(equal(m2, ans_m2));
    Matrix<float, 3, 4> m3(m2);
    EXPECT_TRUE(equal(m3, ans_m2));
    int ans_m4[4][1] = {{5}, {5}, {5}, {5}};
    Vector<int, 4, true> v1(5);
    Matrix<int, 4, 1> m4(v1);
    EXPECT_TRUE(equal(m4, ans_m4));
}

TEST(MatrixTest, TestIndexes) {
    // test index getters (index, get row and column, get diagonal)
    int ans_m[3][4] = {{1, 2, 3, 4}, {1, 3, 5, 7}, {2, 4, 6, 8}};
    Matrix<int, 3, 4> m(ans_m);
    EXPECT_EQ(m(0, 3), 4);

    Vector<int, 3, true> v1 = m.get_col(0);
    int ans_v1[3] = {1, 1, 2};
    EXPECT_TRUE(equal(v1, ans_v1));

    Vector<int, 4> v2 = m.get_row(0);
    int ans_v2[4] = {1, 2, 3, 4};
    EXPECT_TRUE(equal(v2, ans_v2));

    int ans[3] = {1, 3, 6};
    EXPECT_TRUE(equal(m.diagonal(), ans));
}

TEST(MatrixTest, TestMatrixOperators) {
    // test Matrix operations on Matrix
    int ans_sum[3][2] = {{7, 7}, {7, 7}, {7, 7}};
    int ans_mult[3][2] = {{6, 10}, {12, 12}, {10, 6}};
    int sum1[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int sum2[3][2] = {{6, 5}, {4, 3}, {2, 1}};
    Matrix<int, 3, 2> m1(sum1);
    Matrix<int, 3, 2> m2(sum2);
    EXPECT_TRUE(equal(m1 + m2, ans_sum));
    m1 += m2;
    EXPECT_TRUE(equal(m1, ans_sum));
    EXPECT_TRUE(equal(m1 - m2, sum1));
    m1 -= m2;
    EXPECT_TRUE(equal(m1, sum1));
    EXPECT_TRUE(equal(m1.mult(m2), ans_mult));
    m1 = m1.mult(m2);
    EXPECT_TRUE(equal(m1, ans_mult));

    int matr3[2][3] = {{1, 2, 2}, {3, 1, 1}};
    Matrix<int, 2, 3> m3(matr3);
    int matr4[3][2] = {{4, 2}, {3, 1}, {1, 5}};
    Matrix<int, 3, 2> m4(matr4);
    int matr_mult[2][2] = {{12, 14}, {16, 12}};
    EXPECT_TRUE(equal(m3 * m4, matr_mult));
}

TEST(MatrixTest, TestOperatorsWithNum) {
    // Test operations with other data types
    float ans_num[3][3] = {{1.5, 3, 4.5}, {6, 7.5, 9}, {10.5, 12, 13.5}};
    float matr_num[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<float, 3, 3> m1(matr_num);
    EXPECT_TRUE(equal(m1 * 1.5, ans_num));
    m1 *= 1.5;
    EXPECT_TRUE(equal(m1, ans_num));
    float ans_num_sum[3][3] = {{3, 4.5, 6}, {7.5, 9, 10.5}, {12, 13.5, 15}};
    EXPECT_TRUE(equal(m1 + 1.5, ans_num_sum));
    m1 += 1.5;
    EXPECT_TRUE(equal(m1, ans_num_sum));
    EXPECT_TRUE(equal(m1 - 1.5, ans_num));
    m1 -= 1.5;
    EXPECT_TRUE(equal(m1, ans_num));
}

TEST(MatrixTest, TestOperatorsWithVector) {
    float matr_num[3][3] = {{1.5, 3, 4.5}, {6, 7.5, 9}, {10.5, 12, 13.5}};
    Matrix<float, 3, 3> m1(matr_num);
    float vect[3] = {1, 2, 3};
    Vector<float, 3> v1(vect);

    float ans_vect_mult1[3][3] = {{1.5, 6, 13.5}, {6, 15, 27}, {10.5, 24, 40.5}};
    EXPECT_TRUE(equal(m1.mult(v1, 1), ans_vect_mult1));
    float ans_vect_mult2[3][3] = {{1.5, 3, 4.5}, {12, 15, 18}, {31.5, 36, 40.5}};
    EXPECT_TRUE(equal(m1.mult(v1, 0), ans_vect_mult2));
    float ans_vect_sum1[3][3] = {{2.5, 5, 7.5}, {7, 9.5, 12}, {11.5, 14, 16.5}};
    EXPECT_TRUE(equal(m1.add(v1, 1), ans_vect_sum1));
    float ans_vect_sum2[3][3] = {{2.5, 4, 5.5}, {8, 9.5, 11}, {13.5, 15, 16.5}};
    EXPECT_TRUE(equal(m1.add(v1, 0), ans_vect_sum2));
    float ans_vect_sub1[3][3] = {{0.5, 1, 1.5}, {5, 5.5, 6}, {9.5, 10, 10.5}};
    EXPECT_TRUE(equal(m1.sub(v1, 1), ans_vect_sub1));
    float ans_vect_sub2[3][3] = {{0.5, 2, 3.5}, {4, 5.5, 7}, {7.5, 9, 10.5}};
    EXPECT_TRUE(equal(m1.sub(v1, 0), ans_vect_sub2));

    float matr[3][3] = {{2, 4, 0}, {-2, 1, 3}, {-1, 0, 1}};
    float vect_mult[3] = {1, 2, -1};
    Matrix<float, 3, 3> m(matr);
    Vector<float, 3> v(vect_mult);
    float ans[3][1] = {10, -3, -2};
    EXPECT_TRUE(equal(m * v, ans));
}

TEST(MatrixTest, TestTranspose) {
    float matr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<float, 3, 3> m(matr);
    float transpose[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    EXPECT_TRUE(equal(m.transpose(), transpose));

    float matr2[2][3] = {{1, 2, 3}, {4, 5, 6}};
    Matrix<float, 2, 3> m2(matr2);
    float transpose2[3][2] = {{1, 4}, {2, 5}, {3, 6}};
    EXPECT_TRUE(equal(m2.transpose(), transpose2));
}

TEST(MatrixTest, TestDeterminant) {
    float matr[3][3] = {{1, -2, 3}, {4, 0, 6}, {-7, 8, 9}};
    Matrix<float, 3, 3> m(matr);
    EXPECT_EQ(m.determinant(), 204);
    float matr_big[4][4] = {{3, -3, -5, 8}, {-3, 2, 4, -6}, {2, -5, -7, 5}, {-4, 3, 5, -6}};
    Matrix<float, 4, 4> m_big(matr_big);
    EXPECT_EQ(m_big.determinant(), 18);
}

TEST(MatrixTest, TestInverse) {
    float matr[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
    float ans [3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
    Matrix<float, 3, 3> m(matr);
    Matrix<float, 3, 3> m2 = m.inverse();
    EXPECT_TRUE(equal(m2, ans));
}

TEST(VectorTest, TestConstructors) {
    Vector<int, 3> v1;
    int ans_v1[3] = {0, 0, 0};
    EXPECT_TRUE(equal(v1, ans_v1));
    float ans_v2[3] = {1.5, 2.7, 3.2};
    Vector<float, 3, true> v2(ans_v2);
    EXPECT_TRUE(equal(v2, ans_v2));
    Vector<float, 3, true> v3(v2);
    EXPECT_TRUE(equal(v3, ans_v2));
    Vector<float, 3, true> v4(ans_v2);
    Vector<float, 3, true> v5(v4);
    EXPECT_TRUE(equal(v5, ans_v2));
}

TEST(VectorTest, TestVectorOperators) {
    // test Matrix operations on Matrix
    int ans_sum[3] = {7, 7, 7};
    int ans_mult[3] = {6, 12, 10};
    int sum1[3] = {1, 3, 5};
    int sum2[3] = {6, 4, 2};
    Vector<int, 3> v1(sum1);
    Vector<int, 3> v2(sum2);
    EXPECT_TRUE(equal(v1 + v2, ans_sum));
    v1 += v2;
    EXPECT_TRUE(equal(v1, ans_sum));
    EXPECT_TRUE(equal(v1 - v2, sum1));
    v1 -= v2;
    EXPECT_TRUE(equal(v1, sum1));
    EXPECT_TRUE(equal(v1 * v2, ans_mult));
    v1 *= v2;
    EXPECT_TRUE(equal(v1, ans_mult));
}

TEST(VectorTest, TestOperatorsWithNum) {
    // Test operations with num data types
    float ans_num[3] = {1.5, 6,10.5};
    float vect_num[3] = {1, 4, 7};
    Vector<float, 3> v1(vect_num);
    EXPECT_TRUE(equal(v1 * 1.5, ans_num));
    v1 *= 1.5;
    EXPECT_TRUE(equal(v1, ans_num));
    float ans_num_sum[3] = {3, 7.5, 12};
    EXPECT_TRUE(equal(v1 + 1.5, ans_num_sum));
    v1 += 1.5;
    EXPECT_TRUE(equal(v1, ans_num_sum));
    EXPECT_TRUE(equal(v1 - 1.5, ans_num));
    v1 -= 1.5;
    EXPECT_TRUE(equal(v1, ans_num));
}

int main(int argc, char* argv[])

{
    ::testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}
