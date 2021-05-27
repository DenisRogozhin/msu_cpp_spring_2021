#include "filesort.h"


void UpdateFiles (const uint64_t * const buffer, size_t len,  bool odd) {
    std::ifstream old_file;
    std::ofstream new_file;
    if (!odd) {
        old_file.open("odd.txt");
        new_file.open("not_odd.txt");
    } 
    else {
        new_file.open("odd.txt");
        old_file.open("not_odd.txt");
   }
   new_file << std::unitbuf;
   size_t cur = 0;
   size_t mid = len / 2;
   bool written = false;
   while (old_file.peek() != EOF || cur < len / 2 || mid < len) {
       bool read_num = false;
       uint64_t cur_file_num = 0;
       if (old_file.peek() != EOF) {
           old_file >> cur_file_num;
           read_num = true;
       }
       while ((cur < len / 2 && cur_file_num > buffer[cur]) || (mid < len && cur_file_num > buffer[mid]) || (!read_num && (cur < len / 2 || mid < len)) ) {
            if (cur < len / 2 && (mid >= len || buffer[cur] < buffer[mid])) {
                if (written) 
                    new_file << std::endl;
                new_file << buffer[cur];
                written = true;
                cur++;
            } 
            else 
                if (mid < len) {
                    if (written) 
                        new_file << std::endl;
                    new_file << buffer[mid];
                    written = true;
                    mid++;
                 }
       }
       if (read_num) {
           if (written) {
               new_file << std::endl;
           }
           new_file << cur_file_num;
           written = true;
       }
   }
   old_file.close();
   new_file.close();
   if (odd) {
       std::remove("not_odd.txt");
   } 
   else {
       std::remove("odd.txt");
  }
}


std::string FileSort(std::string path) {
    std::ifstream file(path);
    if (!file) { 
        throw std::runtime_error("Can't open file " + path);
    } 
    bool odd = false;
    while (file.peek() != EOF) {
        uint64_t * buffer = new uint64_t[MAX_MEMORY];
        size_t len = 0;
        while (!file.eof() && (len < MAX_MEMORY)) {
            file >> buffer[len];
            len++;
        }
        std::thread first_thread([buffer, len]() {std::sort(buffer, buffer + len / 2);});
        std::thread second_thread([buffer, len]() {std::sort(buffer + len / 2, buffer + len); });
        first_thread.join();
        second_thread.join();
        UpdateFiles(buffer,len,odd);
        odd = !odd; 
        delete []buffer;
    }
    file.close();
    if (odd) {
        std::rename("not_odd.txt", "sorted_file.txt");
        std::remove("odd.txt");
    } 
    else {
        std::rename("odd.txt", "sorted_file.txt");
        std::remove("not_odd.txt");
    }
    return "sorted_file.txt";
}




