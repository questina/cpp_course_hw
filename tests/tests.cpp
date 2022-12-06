#include <gtest/gtest.h>
#include <string>
#include <fstream>

extern "C" {
#include "../libs/toys/toys.h"
#include "../libs/status/status.h"
#include "../libs/manage_data/manage_data.h"
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
    st = add_toy(&toy_store, "TeddyBear", 10, "USA", 20);
    EXPECT_EQ(st.status_code, 0);
    st = add_toy(&toy_store, "Doll", 100000, "USA", 0);
    EXPECT_EQ(st.status_code, 0);
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

TEST(TOYS_CATALOG, TEST_READ_DATA) {
    FILE *f = fopen("tmp.txt", "w+");
    fprintf(f, "1\n");
    fprintf(f, "TeddyBear\n");
    fprintf(f, "10000\n");
    fprintf(f, "USA\n");
    fprintf(f, "100110010111010\n");
    fclose(f);
    f = fopen("tmp.txt", "r");
    struct toy_array toy_store = {0, NULL};
    struct status st{};
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, 0);
    EXPECT_STREQ(st.message, "Success");
    EXPECT_EQ(toy_store.size, 1);
    EXPECT_STREQ(toy_store.toys[0].name, "TeddyBear");
    EXPECT_FLOAT_EQ(toy_store.toys[0].price, 10000);
    EXPECT_STREQ(toy_store.toys[0].country, "USA");
    EXPECT_EQ(toy_store.toys[0].amount, 100110010111010);
    free_data(&toy_store);
}

TEST(TOYS_CATALOG, TEST_WRITE_DATA) {
    FILE *f = fopen("tmp.txt", "w+");
    struct toy_array toy_store = {0, nullptr};
    struct status st;
    st = add_toy(&toy_store, "Lego", 6,"France", 1);
    EXPECT_EQ(st.status_code, 0);
    st = add_toy(&toy_store, "TeddyBear", 10, "USA", 20);
    EXPECT_EQ(st.status_code, 0);
    st = add_toy(&toy_store, "Doll", 100000, "USA", 0);
    EXPECT_EQ(st.status_code, 0);
    write_data(toy_store, f);
    fclose(f);
    std::ifstream file("tmp.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string res_str = buffer.str();
    std::string correct_str = "name = Lego, price = 6.00, country = France, amount = 1\n"
                              "name = TeddyBear, price = 10.00, country = USA, amount = 20\n"
                              "name = Doll, price = 100000.00, country = USA, amount = 0\n";
    EXPECT_EQ(res_str, correct_str);
    free_data(&toy_store);
}

TEST(TOYS_CATALOG, TEST_FIND_INCORRECT_COUNTRY) {
    struct toy_array toy_store = {0, NULL};
    struct status st;
    st = add_toy(&toy_store, "Lego", 6,"France", 1);
    EXPECT_EQ(st.status_code, 0);
    st = add_toy(&toy_store, "TeddyBear", 10, "USA", 20);
    EXPECT_EQ(st.status_code, 0);
    st = add_toy(&toy_store, "Doll", 100000, "USA", 0);
    EXPECT_EQ(st.status_code, 0);
    struct toys_with_status toys_with_st;
    toys_with_st = find_toys_spec_by_country(toy_store, "Russia");
    EXPECT_EQ(toys_with_st.st.status_code, 0);
    EXPECT_STREQ(toys_with_st.st.message, "Success");
    EXPECT_EQ(toys_with_st.toys.size, 0);
    toys_with_st = find_toys_spec_by_country(toy_store, NULL);
    EXPECT_EQ(toys_with_st.st.status_code, -1);
    EXPECT_STREQ(toys_with_st.st.message, "Incorrect toy country passed");
    EXPECT_EQ(toys_with_st.toys.size, 0);
    EXPECT_TRUE(toys_with_st.toys.toys == nullptr);
    free_data(&toy_store);
}

TEST(TOYS_CATALOG, TEST_ADD_INCORRECT_TOY) {
    struct toy_array toy_store = {0, NULL};
    struct status st{};
    st = add_toy(&toy_store, nullptr, 6,"France", 1);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Incorrect toy name passed");
    EXPECT_EQ(toy_store.size, 0);
    st = add_toy(&toy_store, "TeddyBear", 10, nullptr, 20);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Incorrect toy country passed");
    EXPECT_EQ(toy_store.size, 0);
    st = add_toy(nullptr, "Doll", 100000, "USA", 0);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Incorrect store passed");
    EXPECT_EQ(toy_store.size, 0);
}

TEST(TOYS_CATALOG, TEST_INIT_MESSAGE) {
    struct status st{};
    init_message(&st, "Example", 123);
    EXPECT_EQ(st.status_code, 123);
    EXPECT_STREQ(st.message, "Example");
}

TEST(TOYS_CATALOG, TEST_PROCESS_MESSAGE) {
    struct status st{};
    init_message(&st, "Example", -1);
    FILE *f = fopen("tmp.txt", "w+");
    process_message(st, f);
    fclose(f);
    std::ifstream file("tmp.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string res_str = buffer.str();
    std::string correct_str = "Example";
    EXPECT_EQ(res_str, correct_str);
}

TEST(TOYS_CATALOG, INCORRECT_INPUT) {
    FILE *f = fopen("tmp.txt", "w+");
    fclose(f);
    f = fopen("tmp.txt", "r");
    struct toy_array toy_store = {0, NULL};
    struct status st{};
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Could not read store_size");
    EXPECT_EQ(toy_store.size, 0);
    f = fopen("tmp.txt", "w+");
    fprintf(f, "1\n");
    fclose(f);
    f = fopen("tmp.txt", "r");
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Could not allocate memory for toy name");
    EXPECT_EQ(toy_store.size, 0);
    f = fopen("tmp.txt", "w+");
    fprintf(f, "1\n");
    fprintf(f, "Teddybear\n");
    fclose(f);
    f = fopen("tmp.txt", "r");
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Could not read toy price");
    EXPECT_EQ(toy_store.size, 0);
    f = fopen("tmp.txt", "w+");
    fprintf(f, "1\n");
    fprintf(f, "Teddybear\n");
    fprintf(f, "100\n");
    fclose(f);
    f = fopen("tmp.txt", "r");
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Could not allocate memory for toy country");
    EXPECT_EQ(toy_store.size, 0);
    f = fopen("tmp.txt", "w+");
    fprintf(f, "1\n");
    fprintf(f, "Teddybear\n");
    fprintf(f, "100\n");
    fprintf(f, "USA\n");
    fclose(f);
    f = fopen("tmp.txt", "r");
    st = read_data(&toy_store, f);
    fclose(f);
    EXPECT_EQ(st.status_code, -1);
    EXPECT_STREQ(st.message, "Could not read toys amount");
    EXPECT_EQ(toy_store.size, 0);
    free_data(&toy_store);
}