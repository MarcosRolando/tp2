#include "BlockOperator.h"
#include <math.h>
#include <string.h>
#include "CompressedBlock.h"

BlockOperator::BlockOperator(int numbers_per_block) {
	numbers = new uint32_t[numbers_per_block];
	this->numbers_per_block = numbers_per_block;
	max_bits = 0;
	minimum = 0;
}

CompressedBlock BlockOperator::proccess_numbers() {
	int bytes_in_block;
	_find_minimum();
	_rest_minimum();
	_calculate_bits_per_number();
	bytes_in_block = _calculate_bytes_in_block();
	CompressedBlock block(bytes_in_block);
	block.store_minimum(minimum);
	block.store_bits_per_number(max_bits);
	_compress_numbers(block);
	return block;
}

void BlockOperator::_find_minimum() {
	for (int i = 0; i < numbers_per_block; ++i) {
		if (i == 0) {
			minimum = numbers[i];
		} else if (minimum > numbers[i]) {
			minimum = numbers[i];
		}
	}
}

void BlockOperator::_rest_minimum() {
	for (int i = 0; i < numbers_per_block; ++i) {
		numbers[i] = numbers[i] - minimum;
	}
}

void BlockOperator::_calculate_bits_per_number() {
	max_bits = _get_bits(_find_maximum());
}

int BlockOperator::_calculate_bytes_in_block() {
	int bytes = ceil((float)(max_bits*numbers_per_block)/8);
	bytes += 5; /*4 bytes del numero minimo y 1 de la cantidad de bits*/
	return bytes;
}

uint32_t BlockOperator::_find_maximum() {
	uint32_t maximum = 0;
	for (int i = 0; i < numbers_per_block; ++i) {
		if (i == 0) {
			maximum = numbers[i];
		} else if (maximum < numbers[i]) {
			maximum = numbers[i];
		}
	}
	return maximum;
}

uint32_t BlockOperator::_get_bits(uint32_t number) {
	uint32_t bit_counter;
	for(bit_counter = 0; number > 0; ++bit_counter) {
		number = number/2;
	}
	return bit_counter;
}

void BlockOperator::_shift_bits(uint32_t& number, uint32_t bits_to_shift,
											uint32_t& bits1, uint32_t& bits2) {
	bits2 = number;
	bits2 >>= (32-bits_to_shift);
	number <<= bits_to_shift;
	number |= bits1;
	bits1 = bits2;
}

/*Cargo en variables de tipo uint32_t los bits de cada numero para lograr la
 * compresion (opero a nivel bits). Utilizo uint32_t ya que asi no tengo que
 * ocuparme del caso en el que la cantidad de bits que representan al numero
 * sea mayor a la de la variable donde lo cargo (ej tener que cargar 12 bits
 * en un uint8_t) dado que como maximo cada numero ocupa 4 bytes(32 bits).
 * Siempre desplazo la cantidad de bits necesaria (max_bits) para cargar el
 * siguiente numero, el cual lo cargo siempre en el ultimo elemento del array
 * de forma que al final me quede el formato en big endian.*/

void BlockOperator::_compress_numbers(CompressedBlock& block) {
	int size = ceil((float)(max_bits*numbers_per_block)/32);
	uint32_t* comp_numbs = new uint32_t[size];
	memset(comp_numbs, 0, size*sizeof(uint32_t));
	uint32_t bits1 = 0, bits2 = 0;/*auxiliares para pasar bits entre elementos*/
	for (int i = 0; i < numbers_per_block; ++i) {
		bits1 = numbers[i];
		for (int j = size-1; j >= 0; --j){
			_shift_bits(comp_numbs[j], max_bits, bits1, bits2);
		}
	}
	_add_padding(comp_numbs, size);
	block.store_compressed_numbers(comp_numbs, size);
	delete[]comp_numbs;
}

/*Agrego el padding en caso de que los bits no sean multiplo de 8. Utilizo la
 * misma logica que antes pero tan solo muevo de a 1 bit (agregando asi ceros
 * al final).*/
void BlockOperator::_add_padding(uint32_t* comp_numbs, int size) {
	uint32_t bits1 = 0, bits2 = 0;
	int n = static_cast<int>(max_bits)*numbers_per_block;
	while (n%8 != 0) {
		bits1 = 0;
		for (int j = size-1; j >= 0; --j) {
			_shift_bits(comp_numbs[j], 1, bits1, bits2);
		}
		n++;
	}
}

uint32_t* BlockOperator::get_numbers() const {
	return numbers;
}


BlockOperator::~BlockOperator() {
	delete [] numbers;
}

