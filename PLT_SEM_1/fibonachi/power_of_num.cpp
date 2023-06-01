#include <iostream>

using namespace std;

int power(int a, int n)
{
  if(n == 0)
    return 1;
  if(n % 2 == 1)
    return a*power(a, n-1);
  else
  {
    int b = power(a, n/2);
    return b*b;
  }
}

void power_modificated(int a, int n, int *result, bool flag, int tmp)
{
  if(n == 0)
    return;
  if(n % 2 == 0)
  {
    *result *= tmp;
    tmp = a;
    *result *= a;
    power_modificated(a, n-1, result, flag, tmp);
  }
  {
    power_modificated(a, n/2, result, flag, tmp);
  }
  return;
}

int main(int argc, char *argv[])
{
  int a;
  int n;
  int result;
  scanf("%d %d", &a, &n);
  cout << power(a,n) << endl;
  power_modificated(a,n, &result, false, a);
  cout << result << endl;
}
