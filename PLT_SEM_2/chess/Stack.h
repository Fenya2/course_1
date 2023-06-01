#ifndef STACK_H
#define STACH_H

#include "Coord.h"
#include "Queue.h"

class Stack
{
	Node* _head;
	int _size;
public:
	Stack();
	void push(coord);
	coord pop();
	void clear();
	bool isEmpty();
	~Stack();
};

#endif
