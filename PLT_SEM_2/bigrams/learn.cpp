#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "FreqDict.h"
#include "StringEdit.hpp"

int main(int argc, char* argv[])
{
	//ввод
	std::string text;
	std::fstream file;
	file.open(argv[1],std::ios::in);
	std::getline(file,text,'\0');
	file.close();

	text=stredit::lowercase(text);
	
	//делим по знакам препинания
	std::vector<std::string> sentences=stredit::splitOnSentences(text,".,:;!?!\"<>(){}[]/|\t\\\n");
	for(unsigned long i=0;i<sentences.size();++i)
		sentences[i]=stredit::trim(sentences[i]);

	//делим по пробелам
	std::vector<std::string> words;
	for(unsigned long i=0;i<sentences.size();++i)
	{
		std::vector<std::string> tmp=stredit::splitOnWords(sentences[i]," ");
		words.insert(words.end(),tmp.begin(),tmp.end());
	}

	//заполняем частотный словарь
	FreqDict freqDict=FreqDict();
	for(unsigned long i;i<words.size();++i)
	{
		if(words[i]==".")
			continue;
		if(!freqDict.find(words[i]))
			freqDict.addWord(words[i],i);
		else
			freqDict.itAddMatch(i);
	}

	//заполняем биграммы
	std::vector<std::string> keys=freqDict.getKeys();
	std::unordered_map<std::string,FreqDict> bigrams;
	for(unsigned long i=0;i<keys.size();++i)
	{
		freqDict.find(keys[i]);
		std::vector<unsigned long> matches=freqDict.itGetMatches();
		for(unsigned long j=0;j<matches.size();++j)
		{
			if(matches[j]==words.size()-1)
				continue;
			if(words[matches[j]+1]==".")
				continue;
			if(!bigrams[keys[i]].find(words[matches[j]+1]))
				bigrams[keys[i]].addWord(words[matches[j]+1],1);
			else
				bigrams[keys[i]].itAddMatch(1);
		}
	}

	//объединяем биграммы с уже существующими.
	FreqDict::mergeBigrams(bigrams);
	return 0;
}
