//////// FDictNode realisation ////////
#include "FreqDict.h"
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>

FDictNode::FDictNode(std::string word,unsigned long firstMatch)
{
	_word=word;
	_matches.push_back(firstMatch);
	_left=nullptr;
	_right=nullptr;
	_freq=1;
}

void FDictNode::setLeft(FDictNode* left) {_left=left;}

void FDictNode::setRight(FDictNode* right) {_right=right;}

void FDictNode::setFreq(unsigned long freq) {_freq=freq;}

void FDictNode::syncronizeFreq() {_freq=_matches.size();}

void FDictNode::addMatch(unsigned long match) 
{
	_matches.push_back(match);
	_freq++;
}

std::string FDictNode::getWord() {return _word;}

unsigned long FDictNode::getFreq() {return _freq;}

const std::vector<unsigned long> FDictNode::getMatches() {return _matches;}

FDictNode* FDictNode::getLeft() {return _left;}

FDictNode* FDictNode::getRight() {return _right;}

FDictNode::~FDictNode()
{
	delete _left;
	delete _right;
}


//////// FreqDict realisation ////////

FreqDict::FreqDict()
{
	_root=nullptr;
	_iterator=nullptr;
}

void FreqDict::mergeBigrams(std::unordered_map<std::string,FreqDict>& newBigrams)
{
	std::unordered_map<std::string,FreqDict> importedBigrams;
	importBigrams(importedBigrams);

	for(std::unordered_map<std::string,FreqDict>::iterator i=importedBigrams.begin();i!=importedBigrams.end();++i)
	{
		if(newBigrams.find(i->first)==newBigrams.end())
			continue;
		mergeDicts(i->second,newBigrams[i->first]);
	}
	for(std::unordered_map<std::string,FreqDict>::iterator i=newBigrams.begin();i!=newBigrams.end();++i)
	{
		if(importedBigrams.find(i->first)!=importedBigrams.end())
			continue;
		importedBigrams[i->first]=i->second;
	}

	std::fstream fileKeys;
	std::fstream fileValues;
	fileKeys.open("bigrams.keys",std::ios::out);
	if(!fileKeys)
	{
		std::cerr<<"can`t create file"<<std::endl;
		return;
	}
	fileValues.open("bigrams.values",std::ios::out);
	if(!fileValues)
	{
		std::cerr<<"can`t create file"<<std::endl;
		return;
	}

	for(std::unordered_map<std::string,FreqDict>::iterator i=importedBigrams.begin();i!=importedBigrams.end();++i)
	{
		std::vector<std::string> keys=(i->second).getKeys();
		fileKeys<<i->first<<" "<<keys.size()<<std::endl;
		for(unsigned long j=0;j<keys.size();++j)
		{
			(i->second).find(keys[j]);
			fileValues<<(i->second).itGetWord()<<" "<<(i->second).itGetFreq()<<std::endl;
		}
	}
	fileKeys.close();
	fileValues.close();
}

void FreqDict::mergeDicts(FreqDict& a,FreqDict& b)
{
	std::vector<std::string> keys=a.getKeys();
	for(int i=0;i<keys.size();++i)
	{
		if(!b.find(keys[i]))
			continue;
		a.find(keys[i]);
		a.itSetFreq(a.itGetFreq()+b.itGetFreq());
	}
	keys=b.getKeys();
	for(int i=0;i<keys.size();++i)
	{
		if(a.find(keys[i]))
			continue;
		b.find(keys[i]);
		a.addWord(keys[i],1);
		a.find(keys[i]);
		a.itSetFreq(b.itGetFreq());
	}
}

void FreqDict::importBigrams(std::unordered_map<std::string,FreqDict>& bigrams)
{
	std::fstream fileKeys;
	std::fstream fileValues;
	fileKeys.open("bigrams.keys",std::ios::in);
	if(!fileKeys)
		return;
	fileValues.open("bigrams.values",std::ios::in);
	if(!fileValues)
		return;

	std::string keyRecord;
	std::string keyWord;
	unsigned long long bigramsQnt;
	std::string valueRecord;
	std::string valueWord;
	unsigned long valueFreq;

	while(getline(fileKeys,keyRecord))
	{
		std::stringstream ss;
		ss<<keyRecord;
		ss>>keyWord>>bigramsQnt;
		for(int i=0;i<bigramsQnt;++i)
		{
			getline(fileValues,valueRecord);
			std::stringstream ss;
			ss<<valueRecord;
			ss>>valueWord>>valueFreq;
			bigrams[keyWord].addWord(valueWord,1);
			bigrams[keyWord].find(valueWord);
			bigrams[keyWord].itSetFreq(valueFreq);
		}
	}
	fileValues.close();
	fileKeys.close();
}

std::vector<std::string> FreqDict::getKeys()
{
	std::vector<std::string> ret;
	if(!_root)
		return ret;
	std::stack<FDictNode*> stack;
	stack.push(_root);
	FDictNode* seek;
	while(!stack.empty())
	{
		seek=stack.top();
		stack.pop();
		while(seek)
		{
			ret.push_back(seek->getWord());
			if(seek->getLeft())
				stack.push(seek->getLeft());
			seek=seek->getRight();
		}
	}
	return ret;
}


bool FreqDict::find(std::string word)
{
	FDictNode* seek=_root;
	while(seek)
	{
		if(seek->getWord()==word)
		{
			_iterator=seek;
			return true;
		}
		else if(seek->getWord()<word)
			seek=seek->getLeft();
		else
			seek=seek->getRight();
	}
	return false;
}

void FreqDict::addWord(std::string word,unsigned long firstMatch)
{
	FDictNode* leaf=new FDictNode(word,firstMatch);
	FDictNode* seek=_root;
	if(!seek)
	{
		_root=leaf;
		return;
	}
	while(1)
	{
		if(seek->getWord()<word)
		{
			if(!seek->getLeft())
			{
				seek->setLeft(leaf);
				return;
			}
			seek=seek->getLeft();
		}
		else
		{
			if(!seek->getRight())
			{
				seek->setRight(leaf);
				return;
			}
			seek=seek->getRight();
		}
	}
}

void FreqDict::remove(std::string word)
{
	throw "not written";
}

void FreqDict::itAddMatch(unsigned long match=0)
{
	if(!_iterator)
		throw "Not valid iterator.";
	_iterator->addMatch(match);
}

void FreqDict::itSetFreq(unsigned long freq) {_iterator->setFreq(freq);}

std::string FreqDict::itGetWord()
{
	if(!_iterator)
		throw "No valid iterator.";
	return _iterator->getWord();
}

unsigned long FreqDict::itGetFreq()
{
	if(!_iterator)
		throw "No valid iterator.";
	return _iterator->getFreq();
}

std::vector<unsigned long> FreqDict::itGetMatches() {return _iterator->getMatches();}

FreqDict::~FreqDict() {delete _root;}
