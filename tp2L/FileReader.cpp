#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <string>
#include "constants.h"

#define BYTES_TO_READ 4
#define STDIN "-"

FileReader::FileReader() {
	is_stdin = false;
}

FileReader::FileReader(std::string file_name) {
	open(file_name);
}

void FileReader::open(std::string file_name) {
	is_stdin = (file_name == STDIN);
	if (!is_stdin) {
		file.open(file_name, std::ios::binary);
		if (file.fail()) throw FILE_NOT_FOUND;
	}
}

int FileReader::_read_from_stdin(int numbers_per_block, uint32_t* numbers,
																int position) {
	std::cin.seekg(position, std::ios_base::beg);
	for (int i = 0; i < numbers_per_block; ++i) {
		std::cin.read(reinterpret_cast<char*>(&numbers[i]), BYTES_TO_READ);
		if (std::cin.eof()) {
			std::cin.clear();
			if (i != 0) {
				numbers[i] = numbers[i-1];
			} else {
				return REACHED_EOF;
			}
		} else {
			numbers[i] = ntohl(numbers[i]);
		}
	}
	return 0;
}

int FileReader::_read_from_file(int numbers_per_block, uint32_t* numbers,
																int position) {
	file.seekg(position, std::ios_base::beg);
	for (int i = 0; i < numbers_per_block; ++i) {
		file.read(reinterpret_cast<char*>(&numbers[i]), BYTES_TO_READ);
		if (file.eof()) {
			file.clear();
			if (i != 0) {
				numbers[i] = numbers[i-1];
			} else {
				return 1;
			}
		} else {
			numbers[i] = ntohl(numbers[i]);
		}
	}
	return 0;
}

int FileReader::read_numbers(int numbers_per_block, uint32_t* numbers,
																int position) {
	if (is_stdin) {
		return _read_from_stdin(numbers_per_block, numbers, position);
	} else {
		return _read_from_file(numbers_per_block, numbers, position);
	}
}

FileReader::~FileReader() {}

