#include "Coord.h"
#include "Node.h"
#include "Stack.h"

Stack::Stack()
{
	_head=nullptr;
	_size=0;
}

void Stack::push(coord val)
{
	Node* nHead=new Node(val);
	nHead->setNext(_head);
	_head=nHead;
	_size++;
}

coord Stack::pop()
{
	if(_size==0)
	{
		clear();
		throw "stack is empty";
	}
	Node* tmp=_head;
	coord ret=_head->getVal();
	_head=_head->getNext();
	tmp->setNext(nullptr);
	delete tmp;
	_size--;
	return ret;
}

void Stack::clear()
{
	delete _head;
	_size=0;
}

bool Stack::isEmpty()
{
	if(_size==0)
		return true;
	return false;
}

Stack::~Stack() {clear();}
