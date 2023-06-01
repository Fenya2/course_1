#include <iostream>
#include <fstream>
#include "Hashmap.h"
#include "prng.hpp"

int main()
{
	std::fstream file;
	Hashmap hm1 = Hashmap(31, 11);
	Hashmap hm2 = Hashmap(17, 7);
	Hashmap hm3 = Hashmap(101, 2);
	std::string str;
	str.resize(4);
	double prev = 0.1;
	file.open("rand_str.txt", std::ios::out);
	int i=0;
	while(hm1.size() < 10000)
	{
		prev+=0.0001;
		for(int i=0; i < 4; ++i)
		{
			prev=generatePseudoRandonShare(prev);
			str[i] = (char) 33+prev*93;
		}
		hm1.add(str);
		hm2.add(str);
		hm3.add(str);
		i++;
	}
	std::cout << i << std::endl;
	file.close();
	file.open("res.txt", std::ios::out);
	file << hm1.distribution() << std::endl;
	file << hm2.distribution() << std::endl;
	file << hm3.distribution() << std::endl;
	file.close();
	return 0;
}
