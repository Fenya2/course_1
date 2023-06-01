////////// Node realisation //////////
template<typename T> Node<T>::Node(T elem)
{
	_value=elem;
	_nextNode=nullptr;
}

template<typename T> Node<T>::~Node() {delete _nextNode;}

template<typename T> void Node<T>::setNext(Node<T>* node) {_nextNode=node;}

template<typename T> Node<T>* Node<T>::getNext() {return _nextNode;}

template<typename T> T Node<T>::getValue() {return _value;}

////////// List realisation //////////
template<typename T> List<T>::List()
{
	_head=nullptr;
	_tail=nullptr;
	_iterator=nullptr;
	_size=0;
}

template<typename T> List<T>::~List() {clear();}

template<typename T> void List<T>::add(T elem)
{
	Node<T>* nTail=new Node<T>(elem);
	if(_size==0)
	{
		_head=nTail;
		_tail=nTail;
		_iterator=nTail;
		_size++;
		return;
	}
	_tail->setNext(nTail); 
	_tail=nTail;
	_size++;
	return;
}

template<typename T> T List<T>::operator [](int num)
{
	if(num>_size-1||num<0)
		throw "Out of range.";
	Node<T>* seek=_head;
	for(int i=0;i<num;++i)
		seek=seek->getNext();
	return seek->getValue();
}

template<typename T> int List<T>::size() {return _size;}

template<typename T> T* List<T>::toArray()
{
	if(_size==0)
		return nullptr;
	T* arrPtr=new T[_size];
	Node<T>* seek=_head;
	for(int i=0;i<_size;++i)
	{
		arrPtr[i]=seek->getValue();
		seek=seek->getNext();
	}
	return arrPtr;
}

template <typename T> void List<T>::itBeging() {_iterator=_head;}
template <typename T> void List<T>::itNext()
{
	if(!_iterator)
		return;
	_iterator=_iterator->getNext();
}
template <typename T> bool List<T>::itEnd() {return !_iterator;}
template <typename T> T List<T>::itValue() {return _iterator->getValue();}

template<typename T> void List<T>::clear()
{
	delete _head;
	_head=nullptr;
	_tail=nullptr;
	_size=0;
}
