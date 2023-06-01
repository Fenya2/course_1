#ifndef CZ_H
#define CZ_H

#include <string>
#include <vector>
#include <unordered_map>
#include "GameNode.h"
#include "GraphBuilder.h"
#include "Game.h"
#include "Edge.h"

class CrossesZeros
{
	GameNode* _root;
	std::unordered_map<unsigned long long,Edge> _moves;
	GameNode* _gameState;
	std::string _queue;
	std::string _mode;
public:
	CrossesZeros(std::string,std::string);
	void makeTurn(std::string);
	void computeTurn();
	bool isEnd();
	std::string showBoard();
	~CrossesZeros();
};
#endif
