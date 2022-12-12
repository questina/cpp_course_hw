#include <string>
#include <vector>

#include "file_manager.hpp"

class ProcessManager {
public:
    static void RunAndWait(const std::string& script_path,
                           const std::vector<int>& input_files_ids,
                           const std::vector<int>& output_files_ids,
                           const FileManager& file_manager);
};