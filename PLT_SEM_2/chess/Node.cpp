#include "Coord.h"
#include "Node.h"

Node::Node(coord val):_val(val)
{_next=nullptr;}
void Node::setNext(Node* next) {_next=next;}
Node* Node::getNext() const {return _next;}
coord Node::getVal() const {return _val;}
Node::~Node() {delete _next;}
