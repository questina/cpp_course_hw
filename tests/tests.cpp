#include <gtest/gtest.h>
#include <string>
#include <iostream>

extern "C" {
#include "../libs/toys/toys.h"
#include "../libs/error/error.h"
#include "../libs/io/io.h"
}

TEST(TOYS_CATALOG, TEST_ADD_TOY) {
    struct toy_array toy_store = {0, nullptr};
    struct status st;
    st = add_toy(&toy_store, "TeddyBear", 10000.9999999, "Russia", 1000000);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    EXPECT_STREQ(toy_store.toys[0].name, "TeddyBear");
    EXPECT_FLOAT_EQ(toy_store.toys[0].price, 10000.9999999);
    EXPECT_STREQ(toy_store.toys[0].country, "Russia");
    EXPECT_EQ(toy_store.toys[0].amount, 1000000);
    free_data(&toy_store);
    st = add_toy(nullptr, "Toy", 11, "USA", 1000);
    EXPECT_EQ(st.status_code, -1);
}

TEST(TOYS_CATALOG, TEST_FIND_CORRECT_COUNTRY ){
    struct toy_array toy_store = {0, NULL};
    struct status st;
    st = add_toy(&toy_store, "Lego", 6,"France", 1);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    st = add_toy(&toy_store, "TeddyBear", 10, "USA", 20);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    st = add_toy(&toy_store, "Doll", 100000, "USA", 0);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    struct toys_with_status toys_with_st;
    toys_with_st = find_toys_spec_by_country(toy_store, "France");
    EXPECT_EQ(toys_with_st.st.status_code, 0);
    EXPECT_STREQ(toys_with_st.st.message, "Success");
    EXPECT_EQ(toys_with_st.toys.size, 1);
    EXPECT_STREQ(toys_with_st.toys.toys[0].name, "Lego");
    EXPECT_FLOAT_EQ(toys_with_st.toys.toys[0].price, 6.00);
    EXPECT_STREQ(toys_with_st.toys.toys[0].country, "France");
    EXPECT_EQ(toys_with_st.toys.toys[0].amount, 1);
    free_data(&toys_with_st.toys);
    st = add_toy(&toy_store, "Unicorn", 10.999, "USA", 10000000);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    toys_with_st = find_toys_spec_by_country(toy_store, "USA");
    EXPECT_EQ(toys_with_st.st.status_code, 0);
    EXPECT_STREQ(toys_with_st.st.message, "Success");
    EXPECT_EQ(toys_with_st.toys.size, 2);
    EXPECT_STREQ(toys_with_st.toys.toys[0].name, "TeddyBear");
    EXPECT_FLOAT_EQ(toys_with_st.toys.toys[0].price, 10);
    EXPECT_STREQ(toys_with_st.toys.toys[0].country, "USA");
    EXPECT_EQ(toys_with_st.toys.toys[0].amount, 20);
    EXPECT_STREQ(toys_with_st.toys.toys[1].name, "Unicorn");
    EXPECT_FLOAT_EQ(toys_with_st.toys.toys[1].price, 10.999);
    EXPECT_STREQ(toys_with_st.toys.toys[1].country, "USA");
    EXPECT_EQ(toys_with_st.toys.toys[1].amount, 10000000);
    free_data(&toy_store);
    free_data(&toys_with_st.toys);
}