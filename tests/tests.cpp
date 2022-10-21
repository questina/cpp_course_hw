#include <gtest/gtest.h>
#include <string>

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
    free(toy_store.toys);
    add_toy_res = add_toy(nullptr, (char *)"Toy", 11, (char *)"USA", 1000);
    EXPECT_EQ(add_toy_res, -1);
}

TEST(TOYS_CATALOG, TEST_FIND_CORRECT_COUNTRY){
    struct toy_array toy_store = init_data();
    int add_toy_res = add_toy(&toy_store, (char *)"Lego", 6, (char *)"France", 1);
    EXPECT_EQ(add_toy_res, 0);
    testing::internal::CaptureStdout();
    find_toys_spec_by_country(toy_store, "France");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "name = Lego, price = 6.00, amount = 1\n");
    testing::internal::CaptureStdout();
    find_toys_spec_by_country(toy_store, "USA");
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "name = Teddybear, price = 89.99, amount = 50\n"
                      "name = HelloKitty, price = 35.50, amount = 10000\n");
    free(toy_store.toys);
}