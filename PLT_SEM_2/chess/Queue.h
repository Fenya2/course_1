#ifndef QUEUE_H
#define QUEUE_H

#include "Coord.h"
#include "Node.h"

class Queue
{
	Node* _head;
	Node* _tail;
	int _size;
public:
	Queue();
	void push(coord);
	coord pop();
	coord seek() const;
	bool isEmpty() const;
	int size() const;
	void clear();
	~Queue();
};
#endif
