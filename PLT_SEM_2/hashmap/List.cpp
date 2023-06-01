#include <string>

#include "List.h"

////////// ListNode reallisation //////////

ListNode::ListNode(std::string s)
{
	_value = s;
	_next = nullptr;
}

// т.к. удаление одного элемента списка особо не нужно,
// можно сделать так, чтобы потом легко чистить список.
ListNode::~ListNode() {delete _next;}

void ListNode::setNext(ListNode* ln) {_next = ln;}

ListNode* ListNode::next() {return _next;}

std::string ListNode::value() {return _value;}

////////// List reallisation //////////

List::List()
{
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

List::~List() {clear();}

int List::size() {return _size;}

void List::add(std::string s)
{
	ListNode* nt = new ListNode(s);
	if(_size++ == 0)
	{
		_head = nt;
		_tail = nt;
		return;
	}
	(*_tail).setNext(nt);
	_tail = nt;
}

std::string List::operator [] (int n)
{
	if(n > _size -1 || n < 0)
	{
		clear();
		throw "out_of_range exception";
	}
	ListNode* seek = _head;
	for(int i = 0; i < n; ++i)
		seek = (*seek).next();
	return (*seek).value();
}

bool List::contains(std::string s)
{
	if(_size==0)
		return false;
	ListNode* seek = _head;
	for(int i = 0; i < _size; ++i)
	{
		if(seek->value() == s)
			return true;
		seek = seek->next();
	}
	return false;
}

void List::clear()
{
	delete _head;
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}
