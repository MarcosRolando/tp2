#ifndef FILEWRITER_H_
#define FILEWRITER_H_

#include "CompressedBlock.h"
#include <fstream>
#include <string>

class FileWriter{
private:
	std::ofstream file;
	bool is_stdout;
public:
	FileWriter();
	explicit FileWriter(std::string file_name);
	/*Abre el archivo acorde a la direccion provista*/
	void open(std::string file_name);
	/*Escribe en el archivo los numeros compresos correspondientes
	 * al bloque provisto*/
	void write_numbers(CompressedBlock& block);
	virtual ~FileWriter();
};

#endif
