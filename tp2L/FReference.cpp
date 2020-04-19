#include "FReference.h"
#include <iostream>
#include <thread>
#include <vector>
#include "QueueMonitor.h"
#include "FileReaderMonitor.h"
#include "FileWriter.h"
#include "Writer.h"
#include "constants.h"
#include "Compressor.h"

FReference::FReference() {
	thread_amount = 0;
	numbers_per_block = 0;
	queue_limit = 0;
	flag = 0;
}

/*La siguiente funcion sobrepasa el limite de las 15 lineas simplemente por la
 * evaluacion de distintos errores, pero la logica contenida es muy sencilla
 * y no tendria sentido separarla en 2 funciones distintas*/
void FReference::_show_error() {
	switch (flag) {
		case ARGUMENTS_ERROR:
			std::cerr << "./tp <N> <T> <Q> <infile> <outfile>" << std::endl;
		break;
		case FILE_NOT_FOUND:
			std::cerr << "No existe el archivo de entrada" << std::endl;
		break;
		case NUMBER_ERROR:
			std::cerr << "Los numeros por bloque deben ser "
					      "mayores a cero" << std::endl;
		break;
		case THREAD_ERROR:
			std::cerr << "La cantidad de threads debe ser "
					      "mayor a cero" << std::endl;
		break;
		case QUEUE_ERROR:
			std::cerr << "El limite de elementos de las colas debe ser "
					      "mayor a cero" << std::endl;
		break;
	}
}

int FReference::_validate_settings() {
	if (numbers_per_block <= 0) {
		flag = NUMBER_ERROR;
	} else if (thread_amount <= 0) {
		flag = THREAD_ERROR;
	} else if (queue_limit <= 0) {
		flag = QUEUE_ERROR;
	}
	try {
		file_r.open(infile);
	} catch(int e) {
		flag =  FILE_NOT_FOUND;
	}
	return flag;
}

int FReference::_load_settings(int argc, char* argv[]) {
	if (argc != 6) {
		flag = ARGUMENTS_ERROR;
		return flag;
	} else {
		try {
			numbers_per_block = std::stoi(argv[1]);
			thread_amount = std::stoi(argv[2]);
			queue_limit = std::stoi(argv[3]);
		} catch(std::invalid_argument& e) {
			flag = ARGUMENTS_ERROR;
			return flag;
		}
		infile = argv[4];
		outfile = argv[5];
		file_w.open(outfile);
		return _validate_settings();
	}
}

void FReference::_run_compressors(std::vector<QueueMonitor*>& queues,
					  	  	  	  	  	   std::vector<Compressor*>& comps,
										   std::vector<std::thread*>& threads) {
	for (int i = 0; i < thread_amount; ++i) {
		queues[i] = new QueueMonitor(queue_limit);
		comps[i] = new Compressor(numbers_per_block, file_r, *queues[i],
															thread_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress,std::ref(*comps[i]));
	}
}

void FReference::_release_compressors(std::vector<QueueMonitor*>& queues,
											std::vector<Compressor*>& comps,
										   std::vector<std::thread*>& threads) {
	for (int i = 0; i < thread_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
	}
	for (int i = 0; i < thread_amount; ++i) {
		delete queues[i];
		delete comps[i];
	}
}

int FReference::run(int argc, char* argv[]) {
	if (_load_settings(argc, argv)) {
		_show_error();
		return 1;
	}
	std::vector<QueueMonitor*> queues(thread_amount);
	std::vector<Compressor*> comps(thread_amount);
	std::vector<std::thread*> threads(thread_amount);
	_run_compressors(queues, comps, threads);
	Writer writer(file_w, queues);
	writer.write();
	_release_compressors(queues, comps, threads);
	return 0;
}

FReference::~FReference() {}

