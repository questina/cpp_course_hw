#include <fstream>
#include <string>
#include <sstream>

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

    void write_one_line(const std::string& str);

    void fflush();

    void write_string(const std::string& string);

    BufferedWriter& operator<<(const std::string& string);
};