#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <thread>
#include <memory>

#include <boost/process.hpp>
#include "file_manager.hpp"

namespace bp = boost::process;

class ProcessManager {
private:
    std::string input_file;
    std::string output_file;
    int buffer_size = 10000;
public:
    explicit ProcessManager(const std::string& in_filename,
                            const std::string& out_filename,
                            int buffer_size=10000);

    void DivideAndRun();

    static void RunProcesses(const std::string& script_path,
                           const std::vector<int>& input_files_ids,
                           const std::vector<int>& output_files_ids,
                           const FileManager& file_manager);


};

void ProcessManager::RunProcesses(
        const std::string& script_path,
        const std::vector<int>& input_files_ids,
        const std::vector<int>& output_files_ids,
        const FileManager& file_manager) {
    int processes_number = input_files_ids.size();
    int processes_per_cycle = std::thread::hardware_concurrency();

    std::map<int, std::unique_ptr<bp::child>> processes;
    int passed_processes = 0;

    while (passed_processes < processes_number || !processes.empty()) {
        int old_processes_to_rerun = processes.size();

        int new_processes_to_run = std::min(
                processes_per_cycle,
                processes_number - passed_processes);
        new_processes_to_run -= old_processes_to_rerun;

        for (int i = passed_processes;
             i < passed_processes + new_processes_to_run; ++i) {
            processes.emplace(i, nullptr);
        }
        if (new_processes_to_run > 0) {
            passed_processes += new_processes_to_run;
        }
        for (auto&[index, process]: processes) {
            process = std::make_unique<bp::child>(
                    script_path,
                    file_manager.get_filename(input_files_ids[index]),
                    file_manager.get_filename(output_files_ids[index]));
        }
        auto it = processes.begin();
        while (it != processes.end()) {
            it->second->wait();
            if (it->second->exit_code() != 0) {
                it->second = nullptr;
                ++it;
            } else {
                it = processes.erase(it);
            }
        }
    }
}

void ProcessManager::DivideAndRun() {
    bp::child compile_pred("g++ -std=c++20 run_predicative.cpp -o seq.out");
    compile_pred.wait();
    FileManager file_manager;
    auto input_files = file_manager.divide_file_in_blocks(input_file, buffer_size);
    auto output_files = file_manager.create_tmp_files(input_files.size());
    ProcessManager::RunProcesses("seq.out", input_files,
                                 output_files, file_manager);
    file_manager.merge_tmp_files(output_files, output_file);
    file_manager.remove_tmp_files(input_files);

    bp::child rm_exec("rm -f seq.out");
    rm_exec.wait();
}

