#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class BufferedWriter {
private:
    std::ofstream file;
    std::ostringstream buffer;
    int buffer_size = 10000;
    int lines_read = 0;
public:
    BufferedWriter() = default;
    explicit BufferedWriter(const std::string& filename, int buffer_size=10000);
    ~BufferedWriter();

    void open(const std::string& filename);
    void close();

    // void write_one_line(const std::string& str);

    void fflush();

    void write_string(const std::string& string);

    BufferedWriter& operator<<(const std::string& string);
};

BufferedWriter::BufferedWriter(const std::string &filename, int buffer_size) {
    this->open(filename);
    this->buffer_size = buffer_size;
}

BufferedWriter::~BufferedWriter() {
    this->close();
}

void BufferedWriter::open(const std::string &filename) {
    this->close();
    file = std::ofstream{filename};
}

void BufferedWriter::close() {
    if (file.is_open()) {
        this->fflush();
        file.close();
    }
}

void BufferedWriter::fflush() {
    file << buffer.str();
    buffer.str(std::string{});
    lines_read = 0;
}

void BufferedWriter::write_string(const std::string& string) {
    lines_read += 1;
    buffer << string + "\n";

    if (buffer_size != -1 && lines_read >= buffer_size) {
        this->fflush();
    }
}


BufferedWriter& BufferedWriter::operator<<(const std::string& string) {
    write_string(string);
    return *this;
}