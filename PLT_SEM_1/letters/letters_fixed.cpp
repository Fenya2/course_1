#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream input_file;
	ofstream letter_file;
	string pattern[3];
	int pattern_cur = 0;

	input_file.open("pattern.txt");
	if(!input_file.is_open())
    {
		cout << "can't 'open file pattern.txt." << endl;
		return -1;
	}
	
	while(!input_file.eof())
	{
    char cur_sym = input_file.get();
    if(cur_sym == '*')
    {
      pattern_cur++;
      continue;
    }
		pattern[pattern_cur] += cur_sym;
	}
	input_file.close();
	
	input_file.open("names.txt");
	if (!input_file.is_open())
	{
		cout << "file 'names.txt' did not open*." << endl;
		return -1;
	}
	string name;
	while (getline(input_file, name))
	{
		letter_file.open("letter_to_" + name + ".txt");
    if(!letter_file.is_open())
    {
      cout << "Error in opening letter file";
      return -1;
    }
		letter_file << pattern[0] << name << pattern[1] << name << pattern[2];
		letter_file.close();
	}
}
