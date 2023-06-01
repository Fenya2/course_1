#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;

int main()
{
        ifstream pattern_file;
        ifstream names_file;
        ofstream letter_file;

        string names[100];
        string name;
        int names_quant = 0;

        names_file.open("names.txt");
        if (!names_file.is_open())
        {
          cout << "file 'names.txt' did not open*." << endl;
		return 0;
	}
	while (getline(names_file, name))
        {
		names[names_quant] = name;
		names_quant++;
        }
        names_file.close();
    
	pattern_file.open("pattern.txt");
	if(!pattern_file.is_open())
        {
		cout << "can't 'open file pattern.txt." << endl;
		return 0;
	}
	char cur_sym;
	pattern_file.get(cur_sym); // считываем здесь, потому, что если звездочка стоит в конце, имя печатается 2 раза(почему???)
	while(!pattern_file.eof())
	{
		for(int i = 0; i < names_quant; i++)
		{
			letter_file.open("letter_to_" + names[i] + ".txt", ios::app);
			if (!letter_file.is_open())
			{
				cout << "file letter_" << name[i] << "did not open*." << endl;
				return 0;
			}
			
			if(cur_sym == '*')
				letter_file << names[i];
			else
				letter_file << cur_sym;
			letter_file.close();
		}
		pattern_file.get(cur_sym);
	}
	pattern_file.close();
	return 0;
}
