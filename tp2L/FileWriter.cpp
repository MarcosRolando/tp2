#include "FileWriter.h"
#include <fstream>
#include <string>
#include "constants.h"

#define STDOUT "-"

FileWriter::FileWriter() {
	is_stdout = false;
}

FileWriter::FileWriter(std::string file_name) {
	open(file_name);
}

void FileWriter::open(std::string file_name) {
	is_stdout = (file_name == STDOUT);
	if (!is_stdout) {
		file.open(file_name, std::ios::binary);
	}
}

void FileWriter::write_numbers(CompressedBlock& block) {
	char* block_to_write = block.get_buffer();
	int bytes = block.get_bytes();
	if (is_stdout) {
		std::cout.write(block_to_write, bytes);
	} else {
		file.write(block_to_write, bytes);
	}
}

FileWriter::~FileWriter() {}

