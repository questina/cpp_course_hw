#include <gtest/gtest.h>
#include "../../include/process_manager_parallel.cpp"
#include <fstream>

#define ELEMENTS_NUM 10000
#define BUFFER_SIZE  1000

void process(std::string input_file, std::string output_file, std::string script_path, int buffer_size) {
    ProcessManager pm(input_file, output_file, buffer_size);
    pm.DivideAndRun();
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

TEST(unit_test_seq, test_created_one_in_file) {
    std::string input_file = "input.txt";
    int buffer_size = -1;
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    std::vector<int> input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    EXPECT_EQ(input_files.size(), 1);
    std::string output_file = file_manager.get_filename(input_files[0]);
    std::ifstream real_file(input_file);
    std::ifstream gen_file(output_file);
    std::string real_line, gen_line;
    while (std::getline(real_file, real_line) && std::getline(gen_file, gen_line)) {
        EXPECT_EQ(real_line, gen_line);
    }
    EXPECT_FALSE(std::getline(real_file, real_line));
    EXPECT_FALSE(std::getline(gen_file, gen_line));
}

TEST(unit_test_seq, test_created_one_out_file) {
    std::string input_file = "input.txt";
    int buffer_size = -1;
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    EXPECT_EQ(output_files.size(), 1);
}

TEST(unit_test_seq, test_process) {
    std::string input_file = "input.txt";
    int buffer_size = -1;
    std::string script_path = "./seq.out";
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    std::string output_file = file_manager.get_filename(output_files[0]);
    std::ifstream gen_file(output_file);
    std::string gen_line;
    EXPECT_TRUE(std::getline(gen_file, gen_line));
    EXPECT_FALSE(std::getline(gen_file, gen_line));
}

TEST(unit_test_seq, test_output) {
    std::string input_file = "input.txt";
    int buffer_size = -1;
    std::string script_path = "./seq.out";
    std::string output_file = "output.txt";
    std::ofstream outfile (output_file);
    outfile.close();
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    std::string out_file = file_manager.get_filename(output_files[0]);
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    std::ifstream real_file(output_file);
    std::ifstream gen_file(out_file);
    std::string real_line, gen_line;
    while (std::getline(real_file, real_line) && std::getline(gen_file, gen_line)) {
        EXPECT_EQ(real_line, gen_line);
    }
    EXPECT_FALSE(std::getline(real_file, real_line));
    EXPECT_FALSE(std::getline(gen_file, gen_line));
}

TEST(unit_test_seq, test_deleted) {
    std::string input_file = "input.txt";
    int buffer_size = -1;
    std::string script_path = "./seq.out";
    std::string output_file = "output.txt";
    std::ofstream outfile (output_file);
    outfile.close();
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    std::string saved_file = file_manager.get_filename(input_files[0]);
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    file_manager.remove_tmp_files(input_files);
    std::ifstream f(saved_file);
    EXPECT_FALSE(f.good());
}

TEST(unit_test_parallel, test_created_in_file) {
    std::string input_file = "input.txt";
    int buffer_size = BUFFER_SIZE;
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    std::vector<int> input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    EXPECT_EQ(input_files.size(), ELEMENTS_NUM / buffer_size);
    std::ifstream real_file(input_file);
    std::string real_line, gen_line;
    for (auto id: input_files) {
        std::string output_file = file_manager.get_filename(id);
        std::ifstream gen_file(output_file);
        while (std::getline(gen_file, gen_line)) {
            std::getline(real_file, real_line);
            EXPECT_EQ(real_line, gen_line);
        }
    }
    EXPECT_FALSE(std::getline(real_file, real_line));
}

TEST(unit_test_parallel, test_created_out_file) {
    std::string input_file = "input.txt";
    int buffer_size = BUFFER_SIZE;
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    EXPECT_EQ(output_files.size(), ELEMENTS_NUM / buffer_size);
}

TEST(unit_test_parallel, test_process) {
    std::string input_file = "input.txt";
    int buffer_size = BUFFER_SIZE;
    std::string script_path = "./seq.out";
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    std::string gen_line;
    for (auto id: input_files) {
        std::string output_file = file_manager.get_filename(id);
        std::ifstream gen_file(output_file);
        EXPECT_TRUE(std::getline(gen_file, gen_line));
    }
}

TEST(unit_test_parallel, test_output) {
    std::string input_file = "input.txt";
    int buffer_size = BUFFER_SIZE;
    std::string script_path = "./seq.out";
    std::string output_file = "output.txt";
    std::ofstream outfile (output_file);
    outfile.close();
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    std::ifstream real_file(output_file);
    std::string real_line;
    EXPECT_TRUE(std::getline(real_file, real_line));
    EXPECT_FALSE(std::getline(real_file, real_line));
}

TEST(unit_test_parallel, test_deleted) {
    std::string input_file = "input.txt";
    int buffer_size = BUFFER_SIZE;
    std::string script_path = "./seq.out";
    std::string output_file = "output.txt";
    std::ofstream outfile (output_file);
    outfile.close();
    generate_data(input_file);
    FileManager file_manager;
    auto file = std::ifstream{input_file};
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    std::vector<std::string> saved_files;
    for (unsigned int i = 0; i < output_files.size(); i++) {
        saved_files.push_back(file_manager.get_filename(output_files[i]));
    }
    ProcessManager::RunProcesses(script_path, input_files,
                               output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    file_manager.remove_tmp_files(input_files);
    for (const auto& saved_file: saved_files) {
        std::ifstream f(saved_file);
        EXPECT_FALSE(f.good());
    }
}

TEST(compare, equal_results) {
    generate_data("input.txt");
    std::ofstream outfile_seq ("output_seq.txt");
    outfile_seq.close();
    std::ofstream outfile_par ("output_par.txt");
    outfile_par.close();
    int buffer_size = BUFFER_SIZE;
    process("input.txt", "output_seq.txt", "./seq.out", -1);
    process("input.txt", "output_par.txt", "./seq.out", buffer_size);

    std::ifstream f_seq("output_seq.txt");
    std::ifstream f_par("output_par.txt");
    int res_seq, res_par;
    f_seq >> res_seq;
    f_par >> res_par;
    EXPECT_EQ(res_seq, res_par);
}


