#ifndef FREFERENCE_H_
#define FREFERENCE_H_

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "Compressor.h"
#include "QueueMonitor.h"
#include "FileReaderMonitor.h"
#include "FileWriter.h"


class FReference {
private:
	FileReaderMonitor file_r;
	FileWriter file_w;
	std::string infile, outfile;
	int numbers_per_block, thread_amount, queue_limit, flag;
public:
	FReference();
	/*Ejecuta el TP2 Frame of Reference. Inicio de flujo de codigo del TP.*/
	int run(int argc, char* argv[]);
	virtual ~FReference();
private:
	void _show_error();
	int _load_settings(int argc, char* argv[]);
	int _validate_settings();
	void _run_compressors(std::vector<QueueMonitor*>& queues,
											std::vector<Compressor*>& comps,
											std::vector<std::thread*>& threads);
	void _release_compressors(std::vector<QueueMonitor*>& queues,
											std::vector<Compressor*>& comps,
											std::vector<std::thread*>& threads);
};

#endif
