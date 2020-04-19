#include "QueueMonitor.h"
#include "Queue.h"
#include "CompressedBlock.h"
#include <mutex>
#include <exception>

QueueMonitor::QueueMonitor(unsigned int max_elements) {
	finished_adding = false;
	this->max_elements = max_elements;
	current_elements = 0;
}

void QueueMonitor::push(CompressedBlock p) {
	std::unique_lock<std::mutex> l(queue_mutex);
	while (current_elements == max_elements) {
		cv.wait(l);
	}
	queue.push(std::move(p));
	current_elements++;
	cv.notify_all();
}

CompressedBlock QueueMonitor::pop() {
	std::unique_lock<std::mutex> l(queue_mutex);
	current_elements--;
	cv.notify_all();
	return queue.pop();
}

bool QueueMonitor::empty() {
	std::unique_lock<std::mutex> l(queue_mutex);
	while (queue.empty() && !finished_adding) {
		cv.wait(l);
	}
	return (queue.empty() && finished_adding);
}

void QueueMonitor::done_adding() {
	std::lock_guard<std::mutex> l(queue_mutex);
	finished_adding = true;
	cv.notify_all();
}

QueueMonitor::~QueueMonitor() {}

