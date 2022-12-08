#include "include/sequential/sequential.hpp"
#include <iostream>
#include <vector>

bool predicate(int x) {
    return x < 100;
}

int main() {
    std::vector<int> v{1, 10, 100, 300, 1000};
    std::cout << cnt_true(v, &predicate) << std::endl;
    return 0;
}
