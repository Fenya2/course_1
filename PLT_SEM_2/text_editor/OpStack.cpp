#include "TextEditor.h"
#include <string>

opNode::opNode(opCode CODE, const std::string OPERAND)
{
	code = CODE;
	operand = OPERAND;
	next=nullptr;
}

opNode::~opNode()
{
}

std::string opNode::toString()
{
	return std::to_string((int)code) + " " + operand;
}

OpStack::OpStack()
{
	_head=nullptr;
}

OpStack::~OpStack()
{
	clear();
}

void OpStack::push(opNode* node)
{
	(*node).next=_head;
	_head=node;
}

opNode* OpStack::pop()
{
	if(_head == nullptr)
		return nullptr;
	opNode* res = _head;
	_head = (*_head).next;
	return res;
}
opNode* OpStack::seek()
{
	return _head;
}

bool OpStack::isEmpty()
{
	if(_head == nullptr)
		return true;
	else return false;
}

std::string OpStack::toString()
{
	std::string res = "";
	opNode* node = _head;
	if(_head == nullptr)
		return res;
	while(node != nullptr)
	{
		res += (*node).toString() + "\n";
		node = (*node).next;
	}
	return res;
}

void OpStack::clear()
{
	opNode* n;
	while(!isEmpty())
	{
		n = (*_head).next;
		delete _head;
		_head = n;
	}
}
