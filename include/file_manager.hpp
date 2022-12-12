#include <string>
#include <unordered_map>
#include <vector>

class FileManager {
private:
    int cur_file_id = 0;
    std::unordered_map<int, std::string> tmp_files;
public:
    FileManager() = default;
    ~FileManager();

    std::string get_filename(int file_id) const;
    std::vector<int> divide_file_in_blocks(const std::string& filename, int block_size=10000);

    std::vector<int> create_tmp_files(int id);
    int create_tmp_file();

    void remove_tmp_files(const std::vector<int>& ids);
    void remove_tmp_file(int id);

    void remove_all_tmp_files();

    void merge_tmp_files(const std::vector<int>& files_ids, const std::string& dst_file);
};