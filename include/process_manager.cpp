#include "process_manager.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <thread>

#include <boost/process.hpp>

namespace bp = boost::process;

void ProcessManager::RunAndWait(
        const std::string& script_path,
        const std::vector<int>& input_files_ids,
        const std::vector<int>& output_files_ids,
        const FileManager& file_manager) {
    int processes_number = input_files_ids.size();
    int processes_per_cycle = std::thread::hardware_concurrency();

    std::map<int, std::unique_ptr<bp::child>> processes;
    int passed_processes = 0;
    int failed_processes = 0;

    while (passed_processes < processes_number || !processes.empty()) {
        int old_processes_to_rerun = processes.size();
        failed_processes += old_processes_to_rerun;

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

    std::clog << failed_processes << " processes failed and were rerun"
              << std::endl;
}