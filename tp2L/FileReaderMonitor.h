#ifndef FILEREADERMONITOR_H_
#define FILEREADERMONITOR_H_

#include "FileReader.h"
#include "CompressedBlock.h"
#include <mutex>
#include <iostream>
#include <string>

class FileReaderMonitor {
private:
	FileReader file;
	std::mutex file_mutex;
public:
	FileReaderMonitor();
	explicit FileReaderMonitor(std::string file_name);
	/*Llamado thread-safe del metodo open de FileReader*/
	void open(std::string file_name);
	/*Llamado thread-safe del metodo read_numbers de FileReader*/
	int read_numbers(int numbers_per_block, uint32_t* numbers, int position);
	virtual ~FileReaderMonitor();
};

#endif
