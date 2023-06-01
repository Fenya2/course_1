#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include "List.h"

class Hashmap
{
	List* _table;
	int _size;
	int _tableSize; // Z
	int _hashParam; // # // название не оч
	int hash(std::string);
public:
	Hashmap(int, int);
	~Hashmap();
	int size();
	void add(std::string);
	bool contains(std::string);
	std::string distribution();
	void clear();
};

#endif
