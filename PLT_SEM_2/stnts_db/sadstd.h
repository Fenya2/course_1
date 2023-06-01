#ifndef SADSTD_HPP
#define SADSTD_HPP

#include <iostream>
#include <string>

namespace sadstd
{
	std::string basename(std::string path)
	{
		for(int i=path.size()-1;i>=0;--i)
			if(path[i]=='/')
				return path.substr(i+1);
		return path;
	}

	template<typename T> class Node
	{
		T _value;
		Node<T>* _nextNode;
	public:
		Node(T);
		void setNext(Node<T>*);
		Node<T>* getNext();
		T getValue();
		~Node();
	};

	template<typename T> class List
	{
		int _size;
		Node<T>* _head;
		Node<T>* _tail;
		Node<T>* _iterator;
	public:
		List();
		T operator [](int);
		void add(T);
		int size();
		T* toArray();
		void itBeging();
		void itNext();
		bool itEnd();
		T itValue();
		void clear();
		~List();
	};
	#include "sadstd.cpp"
}

#endif
