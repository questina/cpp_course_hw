#include "include/process_manager_parallel.cpp"

void generate_data(std::string filename, int elem_nums=10000) {
    std::ofstream file (filename);
    srand(42);
    for (int i = 0; i < elem_nums; i++) {
        int elem = rand() % elem_nums;
        file << elem << "\n";
    }
    file.close();
}

int main() {
    generate_data("input.txt", 1000);
    ProcessManager pm("input.txt", "output.txt");
    pm.DivideAndRun();
}