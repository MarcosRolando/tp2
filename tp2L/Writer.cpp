#include "Writer.h"
#include "CompressedBlock.h"
#include <vector>

Writer::Writer(FileWriter& file, std::vector<QueueMonitor*> queues) :
																file(file) {
	this->queues = queues;
}

void Writer::_write_to_file(bool has_queue_finished, int i) {
	if (!has_queue_finished) {
		CompressedBlock block = std::move((*queues[i]).pop());
		file.write_numbers(block);
	}
}

/*Recorro en round robin las colas y escribo a disco. Aux evalua si la cola
 * esta vacia y tan solo cuando todas lo esten (ultimo recorrido) aux sera
 * verdadero y se dara por terminada la escritura. Recordar que el metodo
 * empty de QueueMonitor solo retorna true cuando la cola esta vacia y ya no
 * le van a agregar mas elementos*/

void Writer::write() {
	bool finished = false, aux = true;
	unsigned int i = 0;
	while (!finished) {
		bool has_queue_finished = (*queues[i]).empty();
		_write_to_file(has_queue_finished, i);
		aux = aux && has_queue_finished;
		if (queues.size() == (i+1)) {
			i = 0;
			finished = aux;
			aux = true;
		} else {
			++i;
		}
	}
}

Writer::~Writer() {}

