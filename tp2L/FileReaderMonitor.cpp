#include "FileReaderMonitor.h"
#include <mutex>
#include <iostream>
#include <fstream>
#include <string>

FileReaderMonitor::FileReaderMonitor() {}

FileReaderMonitor::FileReaderMonitor(std::string file_name) : file(file_name){}

void FileReaderMonitor::open(std::string file_name) {
	std::lock_guard<std::mutex> l(file_mutex);
	file.open(file_name);
}

int FileReaderMonitor::read_numbers(int numbers_per_block, uint32_t* numbers,
																int position) {
	std::lock_guard<std::mutex> l(file_mutex);
	return file.read_numbers(numbers_per_block, numbers, position);
}

FileReaderMonitor::~FileReaderMonitor() {}

