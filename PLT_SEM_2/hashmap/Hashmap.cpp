#include <string>
#include <cmath>

#include "Hashmap.h"
#include "List.h"

////////// Hashmap realisation //////////

Hashmap::Hashmap(int ts, int hp)
{
	_tableSize = ts;
	_hashParam = hp;
	_table = new List[_tableSize];
	_size = 0;
}

Hashmap::~Hashmap() {delete [] _table;}

int Hashmap::size() {return _size;}

int Hashmap::hash(std::string s)
{
	int hash = 0;
	for(int i = 0; i < s.size(); ++i)
		hash+= ((int)s[i]) * std::pow(_hashParam, i);
	// max hash for s.size() = 4 : 4*255*(11^3) = 1357620
	// то есть попадаем в диапозон int вполне.
	hash %= _tableSize;
	return hash;
}

void Hashmap::add(std::string s)
{
	if(s.size() > 4)
		throw "str size is too big. Hashmap was written to store strings with length 4";
	if(contains(s))
		return;
	_table[hash(s)].add(s);
	_size++;
}

bool Hashmap::contains(std::string s)
{
	return _table[hash(s)].contains(s);
}

std::string Hashmap::distribution()
{
	std::string distribution = "";
	for(int i = 0; i < _tableSize; ++i)
		distribution += std::to_string(_table[i].size()) + ":";
	return distribution;
}

void Hashmap::clear()
{
	for(int i = 0; i < _size; ++i)
		_table[i].clear();
	_size = 0;
}
