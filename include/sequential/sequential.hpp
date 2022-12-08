#ifndef CPP_COURSE_HW_SEQUENTIAL_H
#define CPP_COURSE_HW_SEQUENTIAL_H

#include <vector>

template<typename T>
int cnt_true(std::vector<T> v, bool (* pred)(T)) {
    int cnt = 0;
    for (T elem : v) {
        if (pred(elem)) {
            cnt += 1;
        }
    }
    return cnt;
}

#endif //CPP_COURSE_HW_SEQUENTIAL_H
