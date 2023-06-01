#include "CrossesZeros.h"
#include <iostream>

CrossesZeros::CrossesZeros(std::string queue,std::string mode)
{
	_root=new GameNode();
	graph_builder::generateGraph(_root,0,nullptr);
	_gameState=_root;
	try
	{
		graph_builder::readWeights(_moves,"weights.es");
	}
	catch(const char[])
	{
		std::vector<GameNode*> outcomes;
		graph_builder::getPosibleOutcomes(outcomes,_root);
		graph_builder::hangGraph(outcomes,_moves);
		graph_builder::saveWeights(_moves,"weights.es");
	}
	_queue=queue;
	if(mode=="E")
	{
		if(queue=="C")
			_mode="C";
		else _mode="Z";
	}
	else if(mode=="M")
		_mode="D";
	else if(mode=="H")
	{
		if(queue=="C")
			_mode="Z"; //это не ошибка
		else _mode="C";
	}
	if(queue=="Z")
		computeTurn();
}

void CrossesZeros::makeTurn(std::string turn)
{
	if(!(game::validateTurn(_queue+turn)))
		return;
	if(!game::canMakeTurn(_queue+turn,_gameState->getState()))
		return;
	std::vector<GameNode*> playerMoves=_gameState->getChildren();
	for(int i=0;i<playerMoves.size();++i)
	{
		if(playerMoves[i]->getState()==game::makeTurn(_queue+turn,_gameState->getState()))
		{
			_gameState=playerMoves[i];
			return;
		}
	}
}

bool CrossesZeros::isEnd()
{
	if(game::noTurns(_gameState->getState()))
		return true;
	if(game::whoWon(_gameState->getState())!='0')
		return true;
	return false;
}

std::string CrossesZeros::showBoard()
{return game::to_string(_gameState->getState());}

void CrossesZeros::computeTurn()
{
	std::vector<GameNode*> posibleMoves=_gameState->getChildren();
	double max=0;
	double cur;
	int moveNum=0;
	unsigned long long pair;
	for(int i=0;i<posibleMoves.size();++i)
	{
		pair=game::generatePair(_gameState->getState(),posibleMoves[i]->getState());
		cur=_moves[pair].specificGravity(_mode);
		if(cur>max)
		{
			moveNum=i;
			max=cur;
		}
	}
	_gameState=posibleMoves[moveNum];
}

CrossesZeros::~CrossesZeros() {delete _root;}
