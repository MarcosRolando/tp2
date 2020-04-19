#ifndef QUEUEMONITOR_H_
#define QUEUEMONITOR_H_

#include "Queue.h"
#include <mutex>
#include <condition_variable>

class QueueMonitor {
private:
	Queue queue;
	unsigned int max_elements, current_elements;
	std::mutex queue_mutex;
	std::condition_variable cv;
	bool finished_adding;
public:
	explicit QueueMonitor(unsigned int max_elements);
	/*Llamado thread-safe al metodo push de la Queue. Aumenta el contador de
	 * elementos de la cola y si el limite es alcanzado se bloquea la misma
	 * hasta que le notifiquen que se ha removido un elemento*/
	void push(CompressedBlock p);
	/*Llamado thread-safe al metodo pop de la Queue. Disminye el contador de
	 * elementos de la cola.*/
	CompressedBlock pop();
	/*Retorna si la cola esta o no vacia, considerando "vacio" cuando la cola
	 * no tiene elementos y ya no le van a agregar mas. Si la cola estuviese
	 * vacia pero todavia le fueran a agregar elementos entonces espero a que
	 * le agreguen algo (la bloqueo) y se lo notifiquen */
	bool empty();
	/*Notifica a la cola que ya no se le agregaran mas elementos*/
	void done_adding();
	virtual ~QueueMonitor();
};

#endif
