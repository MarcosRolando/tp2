#include "FileWriter.h"
#include "QueueMonitor.h"
#include <vector>

#ifndef WRITER_H_
#define WRITER_H_

class Writer {
private:
	FileWriter& file;
	std::vector<QueueMonitor*> queues;
public:
	Writer(FileWriter& file, std::vector<QueueMonitor*> queues);
	/*Escribe los numeros compresos generados por los compresores al archivo
	 * provisto*/
	void write();
	virtual ~Writer();
private:
	void _write_to_file(bool has_queue_finished, int i);
};

#endif
