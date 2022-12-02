#include "Set.hpp"
#include <set>
#include <vector>
#include <gtest/gtest.h>

#define ELEMENTS_NUM 10000000
#define TIME_COEF 1.5

void speed_test(void (* custom_func) (Set<int>& s, int elem),
                void (* std_func) (std::set<int>& s, int elem)) {
    std::vector<int> elems(ELEMENTS_NUM);
    srand(42);
    for (int i = 0; i < ELEMENTS_NUM; i++) {
        elems[i] = rand() % ELEMENTS_NUM;
    }
    Set<int> custom_set(elems.begin(), elems.end());
    std::set<int> std_set(elems.begin(), elems.end());
    int custom_start = clock();
    for (int & elem : elems) {
        custom_func(custom_set, elem);
    }
    int custom_end = clock();
    int std_start = clock();
    for (int & elem : elems) {
        std_func(std_set, elem);
    }
    int std_end = clock();
    EXPECT_LE((custom_end - custom_start) / (std_end - std_start), TIME_COEF);
}

TEST(perfomance_test, test_insert_speed) {
    speed_test([](Set<int> &s, int elem) {s.insert(elem);},
               [](std::set<int> &s, int elem) {s.insert(elem);});
}

TEST(perfomace_test, test_find_speed) {
    speed_test([](Set<int> &s, int elem) {s.find(elem);},
               [](std::set<int> &s, int elem) {s.find(elem);});
}

TEST(perfomace_test, test_erase_speed) {
    speed_test([](Set<int> &s, int elem) {s.erase(elem);},
               [](std::set<int> &s, int elem) {s.erase(elem);});
}