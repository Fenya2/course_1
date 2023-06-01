#define max_length 50
#include <iostream>

using namespace std;

int check_period(int start, int end)
{
	if (end - start == 3)
		return 2;
	else
		return 1;
}

int main()
{
	int a;
	int b;
	
	cout << "a: "; cin >> a;
	if (a > 100 || a < 1)
	{
		cout << "Input error." << endl;
		return 0;
	}
	
	cout << "b: "; cin >> b;
	if (b > 100 || b <= a)
	{
		cout << "Input error." << endl;
		return 0;
	}
	
	int remainders[max_length];
	int answer[max_length];
	
	int cur_remainder = (a*10)%b;
	answer[0] = (a*10)/b;
	remainders[0] = cur_remainder;
	bool match = false;
	int counter = 1;
	int period_idx;
	while(!match && counter < max_length)
	{
		answer[counter] = (remainders[counter-1]*10) / b;
		remainders[counter] = (remainders[counter-1]*10) % b;
		for(int i = 0; i < counter - 1; i++)
		{
			if(remainders[i] == remainders[counter] && answer[i] == answer[counter])
			{
				period_idx = i;
				match = true;
				counter -= 2;
			}
		}
		counter++;
	}
	
	cout << "rmd: ";
	for (int i = 0; i < max_length; i++)
	{
		cout << remainders[i] << " ";
	}
	cout << endl;
	cout << "ans: ";
	for (int i = 0; i < max_length; i++)
	{
		cout << answer[i] << " ";
	}
	cout << endl;
			
	cout << a << "/" << b << " = " << "0.";
	for(int i = 0; i < counter; i++ )
	{
		if(i == period_idx)
			cout << "(";
		cout << answer[i];
	}
  
	cout << ")" << endl;
	return 0;
}
