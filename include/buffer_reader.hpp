#include <fstream>
#include <vector>
#include <deque>

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