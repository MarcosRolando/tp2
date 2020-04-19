#ifndef COMPRESSEDBLOCK_H_
#define COMPRESSEDBLOCK_H_

#include <iostream>

class CompressedBlock {
private:
	uint8_t* block;
	int bytes;
public:
	explicit CompressedBlock(int bytes);
	CompressedBlock(CompressedBlock&& other);
	/*Almacena el numero minimo en el buffer*/
	void store_minimum(uint32_t minimum);
	/*Almacena el byte (que representa la cantidad de bits) en el buffer*/
	void store_bits_per_number(uint32_t max_bits);
	/*Almacena los bits que representan los numeros compresos en el buffer*/
	void store_compressed_numbers(uint32_t* comp_numbs, int size);
	/*Retorna la cantidad de bytes del bloque*/
	int get_bytes() const;
	/*Retorna el buffer listo para ser escrito al archivo*/
	char* get_buffer() const;
	virtual ~CompressedBlock();
};

#endif
