#include "process_manager.hpp"


ProcessManager::ProcessManager(const std::string &in_filename, const std::string &out_filename,
                               int buffer_size) {
    this->input_file = in_filename;
    this->output_file = out_filename;
    this->buffer_size = buffer_size;
}