#include "buffer_reader.hpp"
#include <utility>
#include <string>

void BufferedReader::open(const std::string &filename) {
    this->close();
    file = std::ifstream{filename};
}

BufferedReader::BufferedReader(const std::string &filename, int buffer_size) {
    this->open(filename);
    this->buffer_size = buffer_size;
}

BufferedReader::~BufferedReader() {
    this->close();
}

void BufferedReader::close() {
    if (file.is_open()) {
        file.close();
        buffer.clear();
    }
}

bool BufferedReader::read_from_buffer(std::string* line) {
    if (buffer.empty()) {
        read_in_buffer();
    }
    if (buffer.empty()) {
        return false;
    }
    *line = buffer.front();
    buffer.pop_front();
    return true;
}

void BufferedReader::read_in_buffer() {
    std::string cur_line;
    if (buffer_size == -1) {
        while (std::getline(file, cur_line)) {
            buffer.push_back(cur_line);
        }
    } else {
        while (buffer.size() < buffer_size && std::getline(file, cur_line)) {
            buffer.push_back(cur_line);
        }
    }
}

