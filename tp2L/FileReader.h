#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <fstream>
#include <string>

class FileReader{
private:
	std::ifstream file;
	bool is_stdin;
public:
	FileReader();
	explicit FileReader(std::string file_name);
	/*Abre el archivo acorde a la direccion provista. Si no encuentra el archivo
	 * tira una exception*/
	void open(std::string file_name);
	/*Lee los numeros del archivo acorde a la posicion inicial provista y la
	 * cantidad de numeros a leer provistos, y los almacena en el puntero
	 * numbers*/
	int read_numbers(int numbers_per_block, uint32_t* numbers, int position);
	virtual ~FileReader();
private:
	int _read_from_stdin(int numbers_per_block, uint32_t* numbers, int position);
	int _read_from_file(int numbers_per_block, uint32_t* numbers, int position);
};

#endif
