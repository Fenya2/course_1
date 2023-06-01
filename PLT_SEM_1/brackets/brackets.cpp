#define deep 100

#include <string>
#include <iostream>

using namespace std;

int main() 
{
	char open_br[deep];
	for(int i = 0; i < size(open_br); i++)
	{
		open_br[i] = '0';
	}
	string seq;
	getline(cin, seq);
	int cur_br_idx = -1;
	int max_deep = 0;; 
	
	for(int i = 0; i < seq.size(); i++)
	{
		if( seq[i] == '(' || seq[i] == '[' )
		{
			cur_br_idx++;
			open_br[cur_br_idx] = seq[i];
			max_deep = max(max_deep, cur_br_idx + 1);
		}
		if( seq[i] == ')' || seq[i] == ']' )
		{
			if ( (open_br[cur_br_idx] == '(' && seq[i] == ')') || (open_br[cur_br_idx] == '[' && seq[i] == ']'))
			{
				open_br[cur_br_idx] = '0';
				cur_br_idx--;
			}
			else 
			{
				cout << "Incorrect exp." << endl;
				return 0;
			}
		}
	}
	
	if(cur_br_idx == -1)
		cout << "Correct exp. Max deep: " << max_deep << endl;
	else
		cout << "Incorrect exp." << max_deep << endl;
	return 0;
}
