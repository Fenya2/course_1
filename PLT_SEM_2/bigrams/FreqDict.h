#ifndef FREQ_DICT_H
#define FREQ_DICT_H

#include <string>
#include <vector>
#include <unordered_map>

class FDictNode
{
	std::string _word;
	std::vector<unsigned long> _matches;
	FDictNode* _left;
	FDictNode* _right;
	unsigned long _freq;
public:
	FDictNode(std::string,unsigned long);
	void setLeft(FDictNode*);
	void setRight(FDictNode*);
	void setFreq(unsigned long);
	void syncronizeFreq();
	void addMatch(unsigned long);
	std::string getWord();
	unsigned long getFreq();
	const std::vector<unsigned long> getMatches();
	FDictNode* getLeft();
	FDictNode* getRight();
	~FDictNode();
};

class FreqDict
{
public:
	FreqDict();
	static void mergeBigrams(std::unordered_map<std::string,FreqDict>&);
	static void mergeDicts(FreqDict&,FreqDict&);
	static void importBigrams(std::unordered_map<std::string,FreqDict>&);
	std::vector<std::string> getKeys();
	bool find(std::string);
	void addWord(std::string,unsigned long);
	void remove(std::string);
	void itAddMatch(unsigned long);
	void itSetFreq(unsigned long);
	std::string itGetWord();
	unsigned long itGetFreq();
	std::vector<unsigned long> itGetMatches();
	~FreqDict();
private:
	FDictNode* _iterator;
	FDictNode* _root;
};
#endif
