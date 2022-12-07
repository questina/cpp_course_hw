#include "../include/Set.hpp"
#include <vector>
#include <gtest/gtest.h>

TEST(unit_test, test_insert) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    for (int i = 0; i < insert_num; i++) {
        EXPECT_EQ(*s.find(i), i);
    }
    EXPECT_EQ(s.size(), insert_num);
}

TEST(unit_test, test_find) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    for (int i = 0; i < insert_num; i++) {
        EXPECT_EQ(*s.find(i), i);
    }
    for (int i = insert_num; i < 2 * insert_num; i++) {
        EXPECT_TRUE(s.find(i) == s.end());
    }
}

TEST(unit_test, test_erase) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    for (int i = 0; i < insert_num; i += 2) {
        s.erase(i);
    }
    EXPECT_EQ(s.size(), insert_num / 2);
    for (int i = 0; i < insert_num; i++) {
        if (i % 2 == 0) {
            EXPECT_TRUE(s.find(i) == s.end());
        } else {
            EXPECT_EQ(*s.find(i), i);
        }
    }
}

TEST(unit_test, test_empty) {
    int insert_num = 10;
    Set<int> s;
    EXPECT_TRUE(s.empty());
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    EXPECT_FALSE(s.empty());
    for (int i = 0; i < insert_num; i++) {
        s.erase(i);
    }
    EXPECT_TRUE(s.empty());
}

TEST(unit_test, lower_bound) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    for (int i = 0; i < insert_num; i++) {
        EXPECT_EQ(*s.lower_bound(i), i);
    }
}

TEST(unit_test, iterator_constructor) {
    int insert_num = 10;
    std::vector<int> v(insert_num);
    for (int i = 0; i < insert_num; i++) {
        v[i] = i;
    }
    Set<int> s(v.begin(), v.end());
    EXPECT_EQ(s.size(), insert_num);
    for (int i = 0; i < insert_num; i++) {
        EXPECT_EQ(*s.find(i), i);
    }
}

TEST(unit_test, init_list_constructor) {
    Set<int> s{0, 1, 2, 3, 4};
    EXPECT_EQ(s.size(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(*s.find(i), i);
    }
}

TEST(unit_test, other_set_constructor) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    Set<int> other(s);
    for (int i = 0; i < insert_num; i++) {
        EXPECT_EQ(*s.find(i), i);
    }
}

TEST(unit_test, iterator) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    int i = 0;
    for (int it : s) {
        EXPECT_EQ(it, i);
        i += 1;
    }
    i -= 1;
    auto it = s.end();
    it--;
    while (it != s.begin()) {
        EXPECT_EQ(*it, i);
        i -= 1;
        it--;
    }
}
