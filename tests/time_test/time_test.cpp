#include <gtest/gtest.h>
#include <iostream>
#include "../../include/process_manager.hpp"
#include "boost/chrono.hpp"

using namespace boost::chrono;

#define ELEMENTS_NUM 100000000
#define BUFFER_SIZE 1000000

void time_processes(std::string input_file, std::string output_file, std::string script_path, int buffer_size) {
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    file_manager.remove_tmp_files(input_files);
}

void generate_data(std::string filename) {
    std::ofstream file (filename);
    srand(42);
    for (int i = 0; i < ELEMENTS_NUM; i++) {
        int elem = rand() % ELEMENTS_NUM;
        file << elem << "\n";
    }
    file.close();
}

TEST(perfomance_test, compare) {
    generate_data("input.txt");
    std::ofstream outfile ("output.txt");
    outfile.close();
    auto start = system_clock::now();
    time_processes("input.txt", "output.txt", "./seq.out", -1);
    auto end = system_clock::now();
    milliseconds seq_time = duration_cast<milliseconds>(end - start);

    start = system_clock::now();
    time_processes("input.txt", "output.txt", "./seq.out", BUFFER_SIZE);
    end = system_clock::now();
    milliseconds parallel_time = duration_cast<milliseconds>(end - start);

    EXPECT_GT(seq_time, parallel_time);
}