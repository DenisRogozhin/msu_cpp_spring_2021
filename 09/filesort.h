#pragma once



#include <fstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <iostream>
#include <vector>
#include <cassert> 


#define MAX_MEMORY 838860


void UpdateFiles (const uint64_t * const buffer, size_t len,  bool odd);
std::string FileSort(std::string path);

