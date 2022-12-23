#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "include/predicate.cpp"

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

std::vector<int> read_file(std::string filename) {
    std::vector<int> nums;
    std::ifstream filein(filename);
    for (std::string line; std::getline(filein, line); )
    {
        nums.push_back(std::stoi(line));
    }
    filein.close();
    return nums;
}

void write_file(std::string filename, int cnt) {
    std::ofstream fileout(filename);
    fileout << cnt;
    fileout.close();
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Incorrect number of arguments" << std::endl;
        return 1;
    }
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    int cnt = cnt_true(read_file(input_file), predicate);
    write_file(output_file, cnt);
}