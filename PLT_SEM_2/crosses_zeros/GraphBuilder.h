#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "Edge.h"
#include "GameNode.h"
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "Game.h"

namespace graph_builder
{
	void generateGraph(GameNode*,unsigned int,GameNode*);
	void getPosibleOutcomes(std::vector<GameNode*>&,GameNode*);
	void hangGraph(const std::vector<GameNode*>&,std::unordered_map<unsigned long long,Edge>&);
	void saveWeights(std::unordered_map<unsigned long long,Edge>&,const std::string&);
	void readWeights(std::unordered_map<unsigned long long,Edge>&,const std::string&);

}
#endif
