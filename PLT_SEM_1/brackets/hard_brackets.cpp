#include <string>
#include <iostream>

//fix

using namespace std;

int main ()
{
	string seq;
	getline(cin, seq);
	int open_br_cnt = 0;
	int close_br_cnt = 0;
	char cur_br;
	int cur_br_index = -1;
	int max_deep = 0;
	int cur_deep = 0;
	for(int i = 0; i < seq.size(); i++)
	{
		if(cur_deep < 0)
		{
			cout << "incorrect exp." << endl;
			return 0;
		}
		if(seq[i] == '[' || seq[i]== '(')
		{
			cur_br = seq[i];
			cur_br_index = i;
			cur_deep++;
			open_br_cnt++;
			continue;
		}
		if( (cur_br == '[' && seq[i] == ']') || (cur_br == '(' && seq[i] == ')') )
		{
			max_deep = max(cur_deep, max_deep);
			cur_deep--;
			close_br_cnt++;
			for(int j = cur_br_index - 1; j >= 0; j--)
			{
				if( seq[j]=='(' || seq[j]=='[' )
				{
					cur_br = seq[j];
					cur_br_index = j;
					break;
				}
			}
			continue;
		}
		if( (cur_br == '[' && seq[i] == ')') || (cur_br == '(' && seq[i] == ']') )
		{
			cout << "incorrect exp." << endl;
			return 0;
		}
		
	}
	if (open_br_cnt	== close_br_cnt) 
		cout << "correct exp. Max deep: " << max_deep << endl;
	else 
		cout << "incorrect exp." << endl;
	return 0;
}

