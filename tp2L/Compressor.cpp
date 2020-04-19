#include <iostream>
#include "CompressedBlock.h"
#include "Compressor.h"
#include "constants.h"

Compressor::Compressor(int numbers_per_block, FileReaderMonitor& file,
				QueueMonitor& queue, int comps_amount, int comp_number)
				: file(file), queue(queue), b_operator(numbers_per_block) {
	this->numbers_per_block = numbers_per_block;
	this->file_position = (comp_number - 1)*numbers_per_block*4;
	this->file_offset = numbers_per_block*4*(comps_amount - 1);
}

void Compressor::compress() {
	bool is_EOF = false;
	while (!is_EOF) {
		if (_compress_block() == REACHED_EOF) {
			is_EOF = true;
		}
	}
	queue.done_adding();
}

int Compressor::_compress_block() {
	int flag;
	uint32_t* numbers = b_operator.get_numbers();
	flag = file.read_numbers(numbers_per_block, numbers, file_position);
	if (flag == REACHED_EOF) return REACHED_EOF;
	file_position += (file_offset + 4*numbers_per_block);
	CompressedBlock block = b_operator.proccess_numbers();
	queue.push(std::move(block));
	return 0;
}

Compressor::~Compressor() {}


