#include "GameNode.h"
#include "Game.h"

GameNode::GameNode(unsigned int state)
{
	_state=state;
	_parent=nullptr;
}

GameNode::GameNode()
{
	_state=0;
	_parent=nullptr;
}

unsigned int GameNode::getState() const
{return _state;}

GameNode* GameNode::getParent() const
{return _parent;}

std::vector<GameNode*> GameNode::getChildren() const
{return _children;} 

void GameNode::setParent(GameNode* parent)
{_parent=parent;}

void GameNode::addChild(GameNode* child)
{_children.push_back(child);}

GameNode::~GameNode()
{
	for(int i=0;i<_children.size();++i)
		delete _children[i];
}
