#ifndef NODE_H
#define NODE_H
class Node
{
	const coord _val;
	Node* _next;
public:
	Node(coord val);
	void setNext(Node* next);
	Node* getNext() const;
	coord getVal() const;
	~Node();
};
#endif
