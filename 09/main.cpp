#include "filesort.h"


#include <random>


void read_from_file (std::vector<uint64_t>& nums, std::string filename) {
    std::ifstream file(filename);
    while (file.peek() != EOF) {
        uint64_t cur_n;
        file >> cur_n;
        nums.push_back(cur_n);
    }
}


void test (size_t size) {
    std::ofstream file("test.txt");
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<uint64_t> distrib(0);
    for (int i = 0; i < size; i++) {
        int x = distrib(gen);
        file << x;
        if (i < size - 1) 
            file << std::endl;
    }
    file.close();
    std::vector<uint64_t> data;
    read_from_file(data, "test.txt");
    std::string res_filename = FileSort("test.txt");
    std::vector<uint64_t> res;
    read_from_file(res, res_filename);
    std::sort(data.begin(), data.end());
    assert(res == data);
    std::remove("test.txt");
    std::remove(res_filename.c_str());
}


int main() {
  test(10);
  std::cout << "Done1!" << std::endl;
  test(100000);
  std::cout << "Done2!" << std::endl;
  test(838868);
  std::cout << "Done3!" << std::endl;
  test(2838868);
  std::cout << "Done4!" << std::endl;
  return 0;
}








