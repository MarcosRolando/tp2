#ifndef QUEUE_H_
#define QUEUE_H_

#include <queue>
#include "CompressedBlock.h"

class Queue {
private:
	std::queue<CompressedBlock> queue;
public:
	Queue();
	/*Agrega el bloque a la cola*/
	void push(CompressedBlock block);
	/*Retorna si la cola esta vacia o no*/
	bool empty() const;
	/*Retorna un elemento de la cola (el mas antiguo). Ademas, lo elimina de
	 * la cola*/
	CompressedBlock pop();
	virtual ~Queue();
};

#endif
