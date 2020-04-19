#include "Queue.h"
#include "CompressedBlock.h"
#include <queue>

Queue::Queue() {}

void Queue::push(CompressedBlock block) {
	queue.push(std::move(block));
}

CompressedBlock Queue::pop() {
	CompressedBlock block = std::move(queue.front());
	queue.pop();
	return block;
}

bool Queue::empty() const {
	return queue.empty();
}

Queue::~Queue() {}

