#ifndef GAME_NODE_H
#define GAME_NODE_H

#include <vector>

class GameNode
{
public:
	GameNode(unsigned int);
	GameNode();
	unsigned int getState() const;
	GameNode* getParent() const;
	std::vector<GameNode*> getChildren() const;
	void setParent(GameNode*);
	void addChild(GameNode*);
	~GameNode();
private:
	unsigned int _state;
	GameNode* _parent;
	std::vector<GameNode*> _children;
};

#endif
