#include <iostream>
#include <string>
#include <cstring>
#include "Queue.h"
#include "Stack.h"

void printPath(std::string,std::string);

int main()
{
	std::string start;
	std::string finish;
	std::cout<<"<start> <finish>:";std::cin>>start>>finish;
	if(start.size()!=2||finish.size()!=2)
	{
		std::cerr<<"input error."<<std::endl;
		return 1;
	}
	if
	(
		start[0]<'A'||start[0]>'H'||start[1]<'1'||start[1]>'8'||
		finish[0]<'A'||finish[0]>'H'||finish[1]<'1'||finish[1]>'8'
	)
	{
		std::cerr<<"out of range"<<std::endl;
		return 2;
	}
	printPath(start,finish);
	return 0;
}
/*
{{A1......A8},
 {........},
 {........},
 {........},
 {........},
 {........},
 {........},
 {H1.......H8}
}
*/
// A8 B8 C8 ...

void printPath(std::string START,std::string FINISH)
{
// подготовка
	coord board[8][8];
	coord start=coord((int)START[0]-'A',(int)START[1]-'1');
	coord finish=coord((int)FINISH[0]-'A',(int)FINISH[1]-'1');
	Queue q=Queue();
// обход
	q.push(start);
	coord seek;
	coord nb;
	while(q.size()>0)
	{
		seek=q.pop();
		for(int x=-2; x<=2;++x)
		{
			for(int y=-2;y<=2;++y)
			{
				if(abs(x)+abs(y)!=3)
					continue;
				nb=coord(seek.x+x,seek.y+y);
				if(nb.valid()&&board[nb.x][nb.y].x==-1)
				{
					q.push(nb);
					board[nb.x][nb.y]=seek;
					if(nb==finish)
					break; 
				}
			}
		}
	}
// формируем ответ
	// добавим координаты в стек. Я же не зря его писал...
	Stack path=Stack();
	seek=finish;
	while(seek!=start)
	{
		path.push(seek);
		seek=board[seek.x][seek.y];
	}
	path.push(start);
// доска для печати
	unsigned char res[8][8];
	memset(&res[0][0],'.',64);
	unsigned char step='0';
// заполняем
	while(!path.isEmpty())
	{
		seek=path.pop();
		res[seek.x][seek.y]=step;
		step++;
	}
// выводим
	for(int i=0;i<8;++i)
	{
		for(int j=0;j<8;++j)
			std::cout<<res[j][7-i];
		std::cout<<std::endl;
	}
}

