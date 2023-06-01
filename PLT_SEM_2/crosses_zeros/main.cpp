#include <iostream>
#include <string>
#include "CrossesZeros.h"

//g++ *.cpp

int main()
{
	std::string queue;
	std::string mode;
	std::cout<<"enter side[C|Z]:";std::cin>>queue;
	if(queue!="Z"&&queue!="C")
		return 1;
	std::cout<<"enter mode[E|M|H]:";std::cin>>mode;
	if(mode!="E"&&mode!="M"&&mode!="H")
		return 2;
	CrossesZeros cz=CrossesZeros(queue,mode);

	std::string turn;
	std::cout<<cz.showBoard()<<std::endl;
	while(1)
	{
		std::cout<<"your turn:";std::cin>>turn;
		cz.makeTurn(turn);
		if(cz.isEnd()) break;
		cz.computeTurn();
		if(cz.isEnd()) break;
		std::cout<<cz.showBoard()<<std::endl;
	}
	std::cout<<cz.showBoard()<<std::endl;
	return 0;
}
