#include "file_manager.hpp"
#include "buffer_reader.hpp"
#include "buffer_writer.hpp"
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace bf = boost::filesystem;

FileManager::~FileManager() {
    remove_all_tmp_files();
}

std::string FileManager::get_filename(int file_id) const {
    return tmp_files.at(file_id);
}

std::vector<int> FileManager::divide_file_in_blocks(const std::string &filename, int block_size) {
    BufferedReader buf_reader(filename, block_size);
    BufferedWriter writer;
    std::vector<int> files_ids;
    int lines_readed = block_size;
    std::string cur_line;
    if (block_size == -1) {
        int new_file_id = create_tmp_file();
        files_ids.push_back(new_file_id);
        writer.open(get_filename(new_file_id));
        lines_readed = 0;
        while (true) {
            bool success = buf_reader.read_from_buffer(&cur_line);
            if (!success) {
                break;
            }
            writer << cur_line;
            ++lines_readed;
        }
    } else {
        while (true) {
            bool success = buf_reader.read_from_buffer(&cur_line);
            if (!success) {
                break;
            }
            if (lines_readed >= block_size) {
                writer.close();
                int new_file_id = create_tmp_file();
                files_ids.push_back(new_file_id);
                writer.open(get_filename(new_file_id));
                lines_readed = 0;
            }
            writer << cur_line;
            ++lines_readed;
        }
    }
    return files_ids;
}

std::vector<int> FileManager::create_tmp_files(int id) {
    std::vector<int> ids;
    ids.reserve(id);
    for (int i = 0; i < id; ++i) {
        ids.push_back(create_tmp_file());
    }
    return ids;
}

int FileManager::create_tmp_file() {
    int id = cur_file_id++;
    std::string filename = bf::unique_path().native();
    std::ofstream tmp_stream(filename);
    tmp_files.emplace(id, std::move(filename));
    return id;
}

void FileManager::remove_tmp_files(const std::vector<int>& ids) {
    for (int file_id: ids) {
        remove_tmp_file(file_id);
    }
}

void FileManager::remove_all_tmp_files() {
    while (!tmp_files.empty()) {
        remove_tmp_file(tmp_files.begin()->first);
    }
}

void FileManager::remove_tmp_file(int id) {
    bf::remove(tmp_files.at(id));
    tmp_files.erase(id);
}

void FileManager::merge_tmp_files(const std::vector<int>& files_ids, const std::string& dst_file) {
    std::ofstream out(dst_file, std::ios::binary);
    int res = 0;
    for (int file_id: files_ids) {
        std::ifstream in(get_filename(file_id), std::ios_base::binary);
        std::string cur_line;
        std::getline(in, cur_line);
        res += std::stoi(cur_line);
        remove_tmp_file(file_id);
    }
    out << res;
}