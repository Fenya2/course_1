#include <string>
#include <vector>
#include <iostream>
#include "FreqDict.h"

int main(int argc, char* argv[])
{
	std::unordered_map<std::string,FreqDict> bigrams;
	FreqDict::importBigrams(bigrams);
	std::string word=argv[1];
	unsigned int numOfWords=std::stoi(argv[2]);
	for(int i=0;i<numOfWords;++i)
	{
		if(bigrams.find(word)==bigrams.end())
		{
			std::cout<<"end of chain."<<std::endl;
			return 0;
		}
		std::vector<std::string> keys=bigrams[word].getKeys();
		int keyNum=0;
		int maxFreq=0;
		int curFreq=0;
		for(int j=0;j<keys.size();++j)
		{
			bigrams[word].find(keys[j]);
			curFreq=bigrams[word].itGetFreq();
			if(curFreq>maxFreq)
			{
				keyNum=j;
				maxFreq=curFreq;
			}
		}
		word=keys[keyNum];
		std::cout<<word<<std::endl;
	}
	return 0;
}
