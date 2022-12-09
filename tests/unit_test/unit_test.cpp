#include "Set.hpp"
#include <vector>
#include <gtest/gtest.h>

TEST(unit_test, test_insert) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    EXPECT_EQ(s.size(), insert_num);
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
    for (int i = insert_num; i < 2 * insert_num; i++) {
        s.erase(i);
    }
    EXPECT_EQ(s.size(), insert_num);
    s.erase(5); // delete root
    EXPECT_EQ(s.size(), insert_num - 1);
    s.insert(5);
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
    for (int i = insert_num - 1; i >= 0; i -= 2) {
        s.erase(i);
    }
    EXPECT_EQ(s.size(), 0);
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
    Set<int> s3;
    Set<int> s4(s3);
    EXPECT_EQ(s4.size(), 0);

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

    i = 0;
    auto s_begin = s.begin();
    for(; s_begin != s.end(); ++s_begin) {
        EXPECT_EQ(*s_begin, i);
        i += 1;
    }
}

TEST(unit_test, reverse_iterator) {
    int insert_num = 10;
    Set<int> s;
    for (int i = 0; i < insert_num; i++) {
        s.insert(i);
    }
    int i = insert_num - 1;
    auto s_end = s.end();
    s_end--;
    for (; s_end != s.begin(); s_end--) {
        EXPECT_EQ(*s_end, i);
        i -= 1;
    }
    i = insert_num - 1;
    s_end = s.end();
    --s_end;
    for(; s_end != s.begin(); --s_end) {
        EXPECT_EQ(*s_end, i);
        i -= 1;
    }
}

TEST(unit_test, set_clean) {
    Set<int> s1{1, 2, 3, 4, 5};
    s1.clean();
    EXPECT_EQ(s1.size(), 0);
    Set<int> s2;
    s2.clean();
    EXPECT_EQ(s2.size(), 0);
}

TEST(unit_test, set_iterator) {
    Set<int> s{1, 2, 3, 4, 5};
    Set<int>::iterator it;
    it = s.begin();
    EXPECT_EQ(*it, 1);
    auto begin = s.begin();
    EXPECT_EQ(*begin, 1);
    auto end = s.end();
    end--;
    while (begin != end) {
        ++begin;
        --end;
    }
    EXPECT_EQ(*begin, *end);
    EXPECT_TRUE(begin == end);
}

TEST(unit_test, assign_operator) {
    Set<int> s{1, 2, 3};
    Set<int> other = s;
    EXPECT_EQ(s.size(), other.size());
    auto other_beg = other.begin();
    auto s_beg = s.begin();
    while (other_beg != other.end()) {
        EXPECT_EQ(*other_beg, *s_beg);
        other_beg++;
        s_beg++;
    }
}