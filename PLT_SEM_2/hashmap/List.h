#ifndef LIST_H
#define LIST_H

#include <string>

class ListNode
{
	std::string _value;
	ListNode* _next;
public:
	ListNode(std::string);
	~ListNode();
	void setNext(ListNode*);
	ListNode* next();
	std::string value();
};

class List
{
	ListNode* _head;
	ListNode* _tail;
	int _size;
public:
	List();
	~List();
	int size();
	void add(std::string);
	std::string operator [] (int);
	bool contains(std::string);
	void clear();
};

#endif
