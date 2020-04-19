#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_
#include <iostream>
#include <string>
#include "FileReaderMonitor.h"
#include "CompressedBlock.h"
#include "QueueMonitor.h"
#include "BlockOperator.h"

class Compressor {
private:
	int numbers_per_block;
	int file_offset;
	int file_position;
	FileReaderMonitor& file;
	QueueMonitor& queue;
	BlockOperator b_operator;

public:
	Compressor(int numbers_per_block, FileReaderMonitor& file,
						QueueMonitor& queue, int comps_amount, int comp_number);
	/*Comprime los numeros del archivo que le provean acorde a su numero
	 * de hilo*/
	void compress();
	virtual ~Compressor();

private:
	int _compress_block();
};

#endif
