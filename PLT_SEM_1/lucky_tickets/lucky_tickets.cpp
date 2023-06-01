#include <iostream>
#include <cmath>
using namespace std;

int exp_ticket(int N, int* arr)
{
  for(int i = 0; i < 6; i++)
  {
    *(arr+i) = N/pow(10, 5-i);
    N %= (int)pow(10, 5-i);
  }
  cout << endl;
  return 0;
}

int assemble_ticket(int* arr)
{
  int ticket = 0;
  for(int i = 0; i < 6; i++)
  {
    ticket += *(arr+i)*pow(10, 5 - i);
  }
  return ticket;
}

int main()
{
  int N;
  cout << "N: "; cin >> N;
  int n[6];
  exp_ticket(N, n);
  
  int first_sum = n[0] + n[1] + n[2];
  int second_sum = n[3] + n[4] + n[5];
  
  if(first_sum == second_sum) {
    cout << "It's lucky ticket :D." << endl;
    return 0;
  }
  
  int next_ticket = -1;
  int previous_ticket = -1;
  
  if(first_sum > second_sum)
  {
    //find next ticket:
    int delta = first_sum - second_sum;
    for(int i = 0; i < 3; ++i)
    {
      if(delta + n[5-i] < 10)
      {
        n[5-i] += delta;
        break;
      }
      delta -= (9 - n[5-i]);
      n[5-i] = 9;
    }
    next_ticket = assemble_ticket(n);
    
    
    //try to find previous ticket
    exp_ticket(N, n);
    int sign_idx = 5;
    int sign_digit = 0;
    for(int i = 3; i < 6; ++i)
    {
      if(n[i] != 0)
      {
        sign_idx = i;
        sign_digit = n[i];
        break;
      }
    }
    
    for(int i = sign_idx + 1; i < 6; ++i)
      n[i] = 0;
    
    
    delta = first_sum - sign_digit;
    int max_filling = (5 - sign_idx) * 9 + sign_digit - 1;
    if(delta > max_filling)
    {
      cout << "Do smth else." << endl;
      return -1;
    }
    // code i dont know yet.
    previous_ticket = assemble_ticket(n);
  }
  
  if(first_sum < second_sum)
  {
    // find previous ticket.
    int delta = second_sum - first_sum;
    for(int i = 0; i < 3; ++i)
    {
      if(delta <= n[5-i])
      {
        n[5-i] -= delta;
        break;
      }
      delta -= n[5-i];
      n[5-i] = 0;
    }
    previous_ticket = assemble_ticket(n);
  }
  
  cout << "prev: " << previous_ticket << endl;
  cout << "cur : " << N << endl;
  cout << "next: " << next_ticket << endl;
}
