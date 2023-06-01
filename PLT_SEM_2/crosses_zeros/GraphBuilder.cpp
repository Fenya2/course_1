#include "GraphBuilder.h"
void graph_builder::generateGraph(GameNode* node,unsigned int turn=0,GameNode* parent=nullptr)
{
	node->setParent(parent);
	if(game::whoWon(node->getState())!='0')
		return;
	for(int i=0;i<9;++i)
	{
		if(game::canMakeTurn(game::turnsQueue[turn%2]+game::fieldsStr[i],node->getState()))
		{
			GameNode* child=new GameNode(game::makeTurn(game::turnsQueue[turn%2]+game::fieldsStr[i],node->getState()));
			generateGraph(child,turn+1,node);
			node->addChild(child);
		}
	}
}

void graph_builder::getPosibleOutcomes(std::vector<GameNode*>& outcomes,GameNode* state)
{
	if(state->getChildren().empty())
	{
		outcomes.push_back(state);
		return;
	}
	for(int i=0;i<state->getChildren().size();++i)
		getPosibleOutcomes(outcomes,state->getChildren()[i]);
}

void graph_builder::hangGraph(const std::vector<GameNode*>& outcomes,std::unordered_map<unsigned long long,Edge>& moves)
{
	for(unsigned int i=0;i<outcomes.size();++i)
	{
		GameNode* child=outcomes[i];
		GameNode* parent=child->getParent();
		unsigned long long pair=game::generatePair(parent->getState(),child->getState());
		switch(game::whoWon(child->getState()))
		{
			case 'C':
				moves[pair]=Edge(1,0,0);
				break;
			case 'Z':
				moves[pair]=Edge(0,1,0);
				break;
			case '0':
				moves[pair]=Edge(0,0,1);
		}
	}
	std::queue<GameNode*> queue;
	for(int i=0;i<outcomes.size();++i)
		queue.push(outcomes[i]->getParent());
	GameNode* child;
	GameNode* parent;
	while(!queue.empty())
	{
		child=queue.front();
		queue.pop();
		parent=child->getParent();
		if(parent==nullptr)
			continue;
		queue.push(parent);
		unsigned long long pair=game::generatePair(parent->getState(),child->getState());
		Edge edge=Edge();
		std::vector<GameNode*> posibleMoves=child->getChildren();
		for(int i=0;i<posibleMoves.size();++i)
		{
			unsigned long long subpair=game::generatePair(child->getState(),posibleMoves[i]->getState());
			edge.summurize(moves[subpair]);
		}
		moves[pair]=edge;
	}
}

void graph_builder::saveWeights(std::unordered_map<unsigned long long,Edge>& edges,const std::string& filename)
{
	std::fstream file;
	file.open(filename,std::ios::out|std::ios::binary);
	if(!file)
		throw "Save error.";
	for(std::unordered_map<unsigned long long,Edge>::iterator i=edges.begin();i!=edges.end();++i)
	{
		unsigned long long p=i->first;
		Edge e=i->second;
		file.write((char*)&p,sizeof(unsigned long long));
		file.write((char*)&e,sizeof(Edge));
	}
	file.close();
}

void graph_builder::readWeights(std::unordered_map<unsigned long long,Edge>& edges,const std::string& filename)
{
	std::fstream file;
	file.open(filename,std::ios::in|std::ios::binary);
	if(!file)
		throw "Read error.";
	unsigned long long pair;
	Edge edge;
	while(!file.eof())
	{
		file.read((char*)&pair,sizeof(unsigned long long));
		file.read((char*)&edge,sizeof(Edge));
		edges[pair]=edge;
	}
	file.close();
}
