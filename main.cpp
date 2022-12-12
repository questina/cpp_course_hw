#include <iostream>
#include <fstream>
#include "include/process_manager.hpp"

int main(int argc, char **argv) {
    // ./program seq input.txt output.txt script_path
    // ./program parallel input.txt output.txt script_path 1000000
    if (argc < 5 or argc > 6) {
        std::cerr << "Incorrect arguments" << std::endl;
    }
    std::string mode = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];
    std::string script_path = argv[4];

    int buffer_size = -1;
    if (mode == "parallel") {
        buffer_size = std::stoi(argv[5]);
    }
    FileManager file_manager;
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunAndWait(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    file_manager.remove_tmp_files(input_files);
}