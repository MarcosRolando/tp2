#ifndef BLOCKOPERATOR_H_
#define BLOCKOPERATOR_H_

#include <iostream>
#include "CompressedBlock.h"

class BlockOperator {
private:
	uint32_t* numbers, max_bits;
	int numbers_per_block;
	uint32_t minimum;

public:
	explicit BlockOperator(int numbers_per_block);

	/*Ejecuta el algoritmo de compresion sobre los numeros que almacena y
	 * retorna el bloque compreso listo para ser almacenado en la cola por el
	 * compresor*/
	CompressedBlock proccess_numbers();
	/*Retorna el array donde almacena los numeros para ser procesados. Se
	 * utiliza para enviarselo al archivo y poder guardarle los numeros*/
	uint32_t* get_numbers() const;
	virtual ~BlockOperator();

private:
	void _rest_minimum();
	int _calculate_bytes_in_block();
	void _calculate_bits_per_number();
	void _find_minimum();
	void _compress_numbers(CompressedBlock& block);
	void _shift_bits(uint32_t& number, uint32_t bits_to_shift, uint32_t& bits1,
															uint32_t& bits2);
	void _add_padding(uint32_t* comp_numbs, int size);
	uint32_t _find_maximum();
	uint32_t _get_bits(uint32_t number);
};

#endif
