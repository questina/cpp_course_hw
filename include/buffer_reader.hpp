#include <fstream>
#include <vector>
#include <deque>
#include <utility>
#include <string>

class BufferedReader {
private:
    std::ifstream file;
    std::deque<std::string> buffer;
    size_t buffer_size = 10000;
public:
    BufferedReader() = default;
    explicit BufferedReader(const std::string& filename, int buffer_size=10000);
    ~BufferedReader();

    void open(const std::string& filename);
    void close();

    bool read_from_buffer(std::string *line);

    void read_in_buffer();
};

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
    unsigned int no_buffer_size = -1;
    if (buffer_size == no_buffer_size) {
        while (std::getline(file, cur_line)) {
            buffer.push_back(cur_line);
        }
    } else {
        while (buffer.size() < buffer_size && std::getline(file, cur_line)) {
            buffer.push_back(cur_line);
        }
    }
}

