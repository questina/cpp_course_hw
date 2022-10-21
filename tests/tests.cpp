#include <gtest/gtest.h>

extern "C" {
#include "toys.h"
}

TEST(TOYS_CATALOG, TEST_ADD_TOY){
    struct toy_array toy_store = {0, nullptr};
    int add_toy_res = add_toy(&toy_store, (char *)"TeddyBear", 10000.9999999,
            (char *)"Russia", 1000000);
    EXPECT_EQ(add_toy_res, 0);
    EXPECT_EQ(toy_store.toys[0].name, "TeddyBear");
    EXPECT_FLOAT_EQ(toy_store.toys[0].price, 10000.9999999);
    EXPECT_EQ(toy_store.toys[0].country, "Russia");
    EXPECT_EQ(toy_store.toys[0].amount, 1000000);
    add_toy_res = add_toy(nullptr, (char *)"Toy", 11, (char *)"USA", 1000);
    EXPECT_EQ(add_toy_res, -1);
}

TEST(TOYS_CATALOG, TEST_FIND_CORRECT_COUNTRY){
    struct toy_array toy_store = init_data();
    int add_toy_res = add_toy(&toy_store, (char *)"Lego", 6, (char *)"France", 1);
    EXPECT_EQ(add_toy_res, 0);

}