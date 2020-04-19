#include "CompressedBlock.h"
#include <string.h>

CompressedBlock::CompressedBlock(int bytes) {
	block = new uint8_t[bytes];
	memset(block, 0, bytes);
	this->bytes = bytes;
}

CompressedBlock::CompressedBlock(CompressedBlock&& other) {
	this->block = other.block;
	this->bytes = other.bytes;
	other.block = nullptr;
	other.bytes = 0;
}

/*Almaceno los 4 bytes que ocupan el numero minimo en los 4 primeros bytes
 * del buffer. Recorro el minimo al reves teniendo en cuenta que el numero
 * almacenado esta en little endian*/
void CompressedBlock::store_minimum(uint32_t minimum) {
	uint8_t* min = reinterpret_cast<uint8_t*>(&minimum);
	for (int i = 0; i < 4; ++i) {
		block[i] = block[i]|min[3-i];
	}
}

/*Almaceno el byte que representa la cantidad de bits que se utilizan para
 * representar a cada numero compreso*/
void CompressedBlock::store_bits_per_number(uint32_t max_bits) {
	block[4] = block[4]|max_bits;
}

/*Cargo los numeros compresos en los bytes restantes del buffer (los primeros
 * 5 ya estan ocupados por el numero minimo de 4 bytes y el byte que indica la
 * cantidad de bits). Cargo el buffer de derecha a izquierda dado que de esta
 * forma puedo cargar primero los bytes menos significativos de cada numero
 * del array comp_numbs, lo que me asegura que no escribire los bytes que
 * pudiesen sobrar en el numero comp_numbs[0], simplificando el algoritmo.
 * Tener en cuenta que cada numero de comp_numbs esta en little endian y lo
 * recorro acorde a como debo guardarlo en el buffer para poder escribir en el
 * formato correcto. Ver informe para mas detalle del algoritmo utilizado.
 * */

void CompressedBlock::store_compressed_numbers(uint32_t* comp_numbs, int size) {
	int current_number = size - 1;
	int byte = 0;
	uint8_t* number = reinterpret_cast<uint8_t*> (&comp_numbs[current_number]);
	for (int i = 0; i < (bytes-5); ++i) {
		block[bytes-1-i] = number[byte];
		byte++;
		if (byte == 4) {
			current_number--;
			byte = 0;
			number = reinterpret_cast<uint8_t*> (&comp_numbs[current_number]);
		}
	}
}

char* CompressedBlock::get_buffer() const {
	return reinterpret_cast<char*>(block);
}

int CompressedBlock::get_bytes() const {
	return bytes;
}


CompressedBlock::~CompressedBlock() {
	if (block != nullptr) {
		delete [] block;
	}
}

