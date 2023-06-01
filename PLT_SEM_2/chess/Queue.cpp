#include "Queue.h"
#include "Coord.h"

Queue::Queue()
{
	_head=nullptr;
	_tail=nullptr;
	_size=0;
}

void Queue::push(coord val)
{
	Node* nTail=new Node(val);
	_size++;
	if(_size==1)
	{
		_head=_tail=nTail;
		return;
	}
	_tail->setNext(nTail);
	_tail=nTail;
	return;
}

coord Queue::pop()
{
	Node* tmp=_head;
	if(_size==0)
	{
		clear();
		throw "Queue is empty";
	}
	coord ret=_head->getVal();
	_head=_head->getNext();
	_size--;
	tmp->setNext(nullptr);
	delete tmp;
	return ret;
}

coord Queue::seek() const {return _head->getVal();}

bool Queue::isEmpty() const
{
	if(_size==0)
		return true;
	return false;
}

int Queue::size() const {return _size;}

void Queue::clear()
{
	delete _head;
	_size=0;
}

Queue::~Queue() {clear();}
